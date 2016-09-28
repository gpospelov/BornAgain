// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataAssistant.cpp
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
#include "GUIHelpers.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "RealDataItem.h"
#include "projectmanager.h"
#include "BornAgainNamespace.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace {
//const QString filter_string = "Intensity File (*.int *.int.gz *.tif *.tif.gz *.txt *.txt.gz);;"
//        "Other (*)";

const QString filter_string = "Intensity File (*.int *.gz *.tif *.txt);;"
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

    OutputData<double> *result(nullptr);

    try {
        std::unique_ptr<OutputData<double>> data(
                    IntensityDataIOFactory::readOutputData(fileName.toStdString()));
        result = createSimlifiedOutputData(*data.get());
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

//! Creates OutputData with simplified axes [0,nxbin]x[0,nybin].

OutputData<double> *ImportDataAssistant::createSimlifiedOutputData(const OutputData<double> &data)
{
    double xmin(0.0), ymin(0.0);

    const IAxis *aX = data.getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis *aY = data.getAxis(BornAgain::Y_AXIS_INDEX);

    double xmax = double(aX->getSize());
    double ymax = double(aY->getSize());

    OutputData<double> *result = new OutputData<double>;
    result->addAxis(FixedBinAxis("X [nbins]", aX->getSize(), xmin, xmax));
    result->addAxis(FixedBinAxis("Y [nbins]", aY->getSize(), ymin, ymax));
    result->setRawDataVector(data.getRawDataVector());

    return result;
}
