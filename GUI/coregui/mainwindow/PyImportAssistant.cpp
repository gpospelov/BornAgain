// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/PyImportAssistant.h
//! @brief     Implements class PyImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PyImportAssistant.h"
#include "AppSvc.h"
#include "mainwindow.h"
#include "projectmanager.h"
#include "GUIHelpers.h"
#include "PyImport.h"
#include "MultiLayer.h"
#include "BABuild.h"
#include "GUIObjectBuilder.h"
#include "ProjectUtils.h"
#include "SysUtils.h"
#include "BornAgainNamespace.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

namespace {

std::string bornagainDir() {

    std::string pythonPath = SysUtils::getenv("PYTHONPATH");
    std::cout << "XXX pythonPath" << pythonPath << std::endl;

    return pythonPath.empty() ? BABuild::buildLibDir() : std::string();
}

}

PyImportAssistant::PyImportAssistant(MainWindow* mainwin)
    : QObject(mainwin)
    , m_mainWindow(mainwin)
{

}

void PyImportAssistant::exec()
{
    auto fileName = fileNameToOpen();

    if (fileName.isEmpty())
        return;

    QString snippet = readFile(fileName);
    if (snippet.isEmpty())
        return;

    QString funcName = getPySampleFunctionName(snippet);
    if (funcName.isEmpty())
        return;

    auto multilayer = createMultiLayer(snippet, funcName);
    if (!multilayer)
        return;

    populateModels(*multilayer, GUIHelpers::baseName(fileName));
}

//! Lets user to select Python file on disk.

QString PyImportAssistant::fileNameToOpen()
{
    QString dirname = AppSvc::projectManager()->userImportDir();

    QString result = QFileDialog::getOpenFileName(m_mainWindow, "Open python script",
            dirname, "Python scripts (*.py)");

    saveImportDir(result);

    return result;
}

//! Saves file location as a future import dir.

void PyImportAssistant::saveImportDir(const QString& fileName)
{
    if (fileName.isEmpty())
        return;

    AppSvc::projectManager()->setImportDir(GUIHelpers::fileDir(fileName));
}

//! Read content of text file and returns it as a multi-line string.
//! Pop-ups warning dialog in the case of failure.

QString PyImportAssistant::readFile(const QString& fileName)
{
    QString result;

    try {
        result = ProjectUtils::readTextFile(fileName);
    } catch (const std::exception& ex) {
        QString message("Can't read the file. \n\n");
        message += QString::fromStdString(std::string(ex.what()));
        GUIHelpers::warning(m_mainWindow, "File read failure.", message);
    }

    return result;
}

//! Returns the name of function which might generate a MultiLayer in Python code snippet.
//! Pop-ups dialog and asks user for help in the case of doubts.

QString PyImportAssistant::getPySampleFunctionName(const QString& snippet)
{
    QString result;

    std::vector<std::string> funcList;
    try {
        funcList = PyImport::listOfFunctions(snippet.toStdString(), bornagainDir());
        for (auto s: funcList)
            qDebug() << "funcList:" << QString::fromStdString(s);

    } catch (const std::exception& ex) {
        QString message("Exception thrown while executing a Python code.\n\n");
        message += QString::fromStdString(std::string(ex.what()));
        GUIHelpers::warning(m_mainWindow, "Python failure",  message);
    }

    if (funcList.empty()) {
        QString message("Python code doesn't contain any functions.\n\n");
        GUIHelpers::warning(m_mainWindow, "Python failure", message);
    }

    if (!funcList.empty())
        result = QString::fromStdString(funcList.front());

    return result;
}

//! Creates a multi-layer by executing a funcName in embedded Python.
//! Function is supposed to be in code provided by 'snippet'.

std::unique_ptr<MultiLayer> PyImportAssistant::createMultiLayer(const QString& snippet,
                                                                const QString& funcName)
{
    std::unique_ptr<MultiLayer> result;

    try {
        result = PyImport::createFromPython(snippet.toStdString(),
                                            funcName.toStdString(), bornagainDir());

    } catch (const std::exception& ex) {
        QString message("Exception thrown while executing a Python code.\n\n");
        message += QString::fromStdString(std::string(ex.what()));
        GUIHelpers::warning(m_mainWindow, "Python failure",  message);
    }

    return result;
}

//! Populates GUI models with domain multilayer.

void PyImportAssistant::populateModels(const MultiLayer& multilayer, const QString& sampleName)
{
    try {
        QString name = sampleName;
        if (multilayer.getName() != BornAgain::MultiLayerType)
            name = sampleName;

        GUIObjectBuilder guiBuilder;
        guiBuilder.populateSampleModel(m_mainWindow->sampleModel(), multilayer, name);
    } catch(const std::exception& ex) {
        QString message("Exception thrown while trying to build GUI models.\n\n");
        message += QString::fromStdString(std::string(ex.what()));
        GUIHelpers::warning(m_mainWindow, "GUIObjectBuilder failure",  message);
    }

    QString message("Seems that import was successfull.\n\n"
                    "Check SampleView for new sample and material editor for new materials.");

    GUIHelpers::information(m_mainWindow, "PyImport", message);
}

