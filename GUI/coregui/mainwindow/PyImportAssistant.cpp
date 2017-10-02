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
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

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

    qDebug() << "onImportFromPythonScript()" << fileName;

    qDebug() << readFile(fileName);

    auto snippet = readFile(fileName);
    auto multilayer = PyImport::createFromPython(snippet.toStdString(),
                                                 "get_sample", BABuild::buildLibDir());

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_mainWindow->sampleModel(), *multilayer, "xxx");
}

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

QString PyImportAssistant::readFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw GUIHelpers::Error("PyImportAssistant::readFile() -> Error. Can't read file '"+
                                fileName+"'");
    QTextStream in(&file);
    return in.readAll();
}
