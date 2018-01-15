// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.cpp
//! @brief     Implements ImportDataUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ImportDataUtils.h"
#include "AppSvc.h"
#include "AxesItems.h"
#include "BornAgainNamespace.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"
#include "IDetector2D.h"
#include "InstrumentItems.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "RealDataItem.h"
#include "RectangularDetectorItem.h"
#include "SphericalDetectorItem.h"
#include "projectmanager.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace
{
const QString filter_string = "Intensity File (*.int *.gz *.tif *.txt);;"
                              "Other (*)";
}

std::unique_ptr<OutputData<double>> ImportDataUtils::ImportData(QString& baseNameOfLoadedFile)
{
    QString dirname = AppSvc::projectManager()->userImportDir();
    QString fileName = QFileDialog::getOpenFileName(0, QStringLiteral("Open Intensity File"),
                                                    dirname, filter_string);

    if (fileName.isEmpty())
        return nullptr;

    QFileInfo info(fileName);
    baseNameOfLoadedFile = info.baseName();

    QString newImportDir = GUIHelpers::fileDir(fileName);
    if (newImportDir != dirname)
        AppSvc::projectManager()->setImportDir(newImportDir);

    std::unique_ptr<OutputData<double>> result;

    try {
        std::unique_ptr<OutputData<double>> data(
            IntensityDataIOFactory::readOutputData(fileName.toStdString()));
        result = CreateSimplifiedOutputData(*data.get());
    } catch (std::exception& ex) {
        QString message = QString("Error while trying to read file\n\n'%1'\n\n%2")
                              .arg(fileName)
                              .arg(QString::fromStdString(std::string(ex.what())));
        QMessageBox::warning(0, "IO Problem", message);
    }

    return result;
}

//! Creates OutputData with simplified axes [0,nxbin]x[0,nybin].

std::unique_ptr<OutputData<double>>
ImportDataUtils::CreateSimplifiedOutputData(const OutputData<double>& data)
{
    if (data.getRank() != 2)
        throw std::runtime_error("ImportDataAssistant::createSimplifiedOutputData() -> Error. "
                                 "Not a two-dimensional data");

    double xmin(0.0), ymin(0.0);

    const IAxis& aX = data.getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis& aY = data.getAxis(BornAgain::Y_AXIS_INDEX);

    double xmax = double(aX.size());
    double ymax = double(aY.size());

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(FixedBinAxis(aX.getName(), aX.size(), xmin, xmax));
    result->addAxis(FixedBinAxis(aY.getName(), aY.size(), ymin, ymax));
    result->setRawDataVector(data.getRawDataVector());

    return result;
}

bool ImportDataUtils::HasSameDimensions(const GISASInstrumentItem* instrumentItem,
                                        const RealDataItem* realDataItem)
{
    QString message;
    return HasSameDimensions(instrumentItem, realDataItem, message);
}

//! Returns trues if [nxbin X nybin] of the detector is the same as in realData.

bool ImportDataUtils::HasSameDimensions(const GISASInstrumentItem* instrumentItem,
                                        const RealDataItem* realDataItem, QString& message)
{
    bool isSame(true);
    message.clear();

    int nxData(0), nyData(0);
    RealDataShape(realDataItem, nxData, nyData);

    int nxDetector(0), nyDetector(0);
    DetectorShape(instrumentItem, nxDetector, nyDetector);

    if (nxData != nxDetector || nyData != nyDetector) {
        isSame = false;
        message = QString("detector [%1x%2], data [%3x%4]")
                      .arg(nxDetector)
                      .arg(nyDetector)
                      .arg(nxData)
                      .arg(nyData);
    }

    return isSame;
}

//! Returns shape of RealDataItem axes.

void ImportDataUtils::RealDataShape(const RealDataItem* realData, int& nx, int& ny)
{
    nx = ny = 0;
    if (const IntensityDataItem* intensityItem = realData->intensityDataItem()) {
        auto xaxis = intensityItem->getItem(IntensityDataItem::P_XAXIS);
        nx = xaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        auto yaxis = intensityItem->getItem(IntensityDataItem::P_YAXIS);
        ny = yaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    }
}

//! Returns shape of Instrument's detector axes.

void ImportDataUtils::DetectorShape(const GISASInstrumentItem* instrumentItem, int& nx, int& ny)
{
    std::unique_ptr<IDetector2D> detector = instrumentItem->detectorItem()->createDetector();
    nx = static_cast<int>(detector->getAxis(0).size());
    ny = static_cast<int>(detector->getAxis(1).size());
}

void ImportDataUtils::SetInstrumentShapeToData(GISASInstrumentItem* instrumentItem,
                                               const RealDataItem* realDataItemItem)
{
    int nxData(0), nyData(0);
    RealDataShape(realDataItemItem, nxData, nyData);
    instrumentItem->detectorItem()->setSize(nxData, nyData);
}
