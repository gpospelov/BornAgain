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
#include "InstrumentItem.h"
#include "AxesItems.h"
#include "DetectorItems.h"
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

    const IAxis &aX = data.getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis &aY = data.getAxis(BornAgain::Y_AXIS_INDEX);

    double xmax = double(aX.size());
    double ymax = double(aY.size());

    OutputData<double> *result = new OutputData<double>;
    result->addAxis(FixedBinAxis(aX.getName(), aX.size(), xmin, xmax));
    result->addAxis(FixedBinAxis(aY.getName(), aY.size(), ymin, ymax));
    result->setRawDataVector(data.getRawDataVector());

    return result;
}

bool ImportDataAssistant::hasSameDimensions(const InstrumentItem *instrumentItem,
                                            const RealDataItem *realDataItem)
{
    QString message;
    return hasSameDimensions(instrumentItem, realDataItem, message);
}

//! Returns trues if [nxbin X nybin] of the detector is the same as in realData.

bool ImportDataAssistant::hasSameDimensions(const InstrumentItem *instrumentItem,
                              const RealDataItem *realDataItem, QString &message)
{
    bool isSame(true);
    message.clear();

    int nxData(0), nyData(0);
    realDataShape(realDataItem, nxData, nyData);

    int nxDetector(0), nyDetector(0);
    detectorShape(instrumentItem, nxDetector, nyDetector);

    if(nxData != nxDetector || nyData != nyDetector) {
        isSame = false;
        message = QString("detector [%1x%2], data [%3x%4]")
                          .arg(nxDetector).arg(nyDetector).arg(nxData).arg(nyData);
    }

    return isSame;
}

//! Returns shape of RealDataItem axes.

void ImportDataAssistant::realDataShape(const RealDataItem *realData, int &nx, int &ny)
{
    nx = ny = 0;
    if(const IntensityDataItem *intensityItem = realData->intensityDataItem()) {
        SessionItem *xaxis = intensityItem->getItem(IntensityDataItem::P_XAXIS);
        nx = xaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        SessionItem *yaxis = intensityItem->getItem(IntensityDataItem::P_YAXIS);
        ny = yaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    }
}

//! Returns shape of Instrument's detector axes.

void ImportDataAssistant::detectorShape(const InstrumentItem *instrumentItem, int &nx, int &ny)
{
    nx = ny = 0;
    DetectorItem *detectorItem = instrumentItem ->detectorItem();
    Q_ASSERT(detectorItem);

    // FIXME Refactor subDetector
    auto subDetector = detectorItem->getGroupItem(DetectorItem::P_DETECTOR);
    Q_ASSERT(subDetector);

    std::unique_ptr<IDetector2D> detector;

    if(auto sphericalDetector = dynamic_cast<SphericalDetectorItem *>(subDetector)) {
        detector = sphericalDetector->createDetector();
    }

    else if(auto rectangularDetector = dynamic_cast<RectangularDetectorItem *>(subDetector)) {
        detector = rectangularDetector->createDetector();
    }

    Q_ASSERT(detector.get());
    nx = detector->getAxis(0).size();
    ny = detector->getAxis(1).size();
}

void ImportDataAssistant::setInstrumentShapeToData(InstrumentItem *instrumentItem,
                                                   const RealDataItem *realDataItemItem)
{
    int nxData(0), nyData(0);
    realDataShape(realDataItemItem, nxData, nyData);

    DetectorItem *detectorItem = instrumentItem ->detectorItem();
    Q_ASSERT(detectorItem);

    // FIXME Refactor subDetector
    auto subDetector = detectorItem->getGroupItem(DetectorItem::P_DETECTOR);
    Q_ASSERT(subDetector);

    if (subDetector->modelType() == Constants::SphericalDetectorType) {
      subDetector->getItem(SphericalDetectorItem::P_PHI_AXIS)
          ->setItemValue(BasicAxisItem::P_NBINS, nxData);
      subDetector->getItem(SphericalDetectorItem::P_ALPHA_AXIS)
          ->setItemValue(BasicAxisItem::P_NBINS, nyData);
    }

    else if (subDetector->modelType() == Constants::RectangularDetectorType) {
        subDetector->getItem(RectangularDetectorItem::P_X_AXIS)
            ->setItemValue(BasicAxisItem::P_NBINS, nxData);
        subDetector->getItem(RectangularDetectorItem::P_Y_AXIS)
            ->setItemValue(BasicAxisItem::P_NBINS, nyData);
    }

    else {
        throw GUIHelpers::Error("ImportDataAssistant::setInstrumentShapeToData() -> Error.");
    }

}
