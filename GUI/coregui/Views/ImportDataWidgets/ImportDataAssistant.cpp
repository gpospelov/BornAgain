// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataWidgets/ImportDataAssistant.cpp
//! @brief     Implements class ImportDataAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ImportDataAssistant.h"
#include "AppSvc.h"
#include "projectmanager.h"
#include "IntensityDataIOFactory.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include <QFileDialog>
#include <QFileInfo>
#include "GUIHelpers.h"
#include <QMessageBox>
#include <QDebug>

namespace {
const QString filter_string = "Intensity File (*.int *.int.gz *.tif *.tif.gz *.txt *.txt.gz);;"
        "Other (*)";
}

OutputData<double> *ImportDataAssistant::importData(QString &baseNameOfLoadedFile)
{
    QString dirname = AppSvc::projectManager()->userImportDir();
    QString fileName = QFileDialog::getOpenFileName(
        0, QStringLiteral("Open Intensity File"), dirname, filter_string);

    if(fileName.isEmpty())
        return nullptr;

    QFileInfo info(fileName);
    baseNameOfLoadedFile = info.baseName();

    QString newImportDir = GUIHelpers::fileDir(fileName);
    if(newImportDir != dirname)
        AppSvc::projectManager()->setImportDir(newImportDir);

    OutputData<double>* result;

    try {
        result = IntensityDataIOFactory::readOutputData(fileName.toStdString());
    } catch (std::exception &ex) {
        QString message = QString("Error while trying to read file\n\n'%1'\n\n%2")
                              .arg(fileName)
                              .arg(QString::fromStdString(std::string(ex.what())));
        QMessageBox::warning(0, "IO Problem", message);
    }
    return result;
}

//! Loads corresponding intensityDataItem from projectDir.

void ImportDataAssistant::loadIntensityData(RealDataItem *realDataItem, const QString &projectDir)
{
    if(IntensityDataItem *intensityItem = realDataItem->intensityDataItem()) {
        QString filename = intensityItem->fileName(projectDir);
        auto data = IntensityDataIOFactory::readOutputData(filename.toStdString());
        intensityItem->setOutputData(data);
    }
}

//! Saves corresponding intensityDataItem to projectDir.

void ImportDataAssistant::saveIntensityData(RealDataItem *realDataItem, const QString &projectDir)
{
    if(IntensityDataItem *intensityItem = realDataItem->intensityDataItem()) {
        QString filename = intensityItem->fileName(projectDir);
        IntensityDataIOFactory::writeOutputData(
                    *intensityItem->getOutputData(), filename.toStdString());
    }
}
