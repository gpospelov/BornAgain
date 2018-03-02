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

int getRank(const RealDataItem& item)
{
    Q_UNUSED(item); // to be extended
    return 2;
}

int getRank(const InstrumentItem& item) {
    if (item.modelType() == Constants::GISASInstrumentType)
        return 2;
    return -1;
}

std::pair<int, int> RealDataShape(const RealDataItem& realData);

std::pair<int, int> DetectorShape(const InstrumentItem& instrumentItem);

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

bool ImportDataUtils::Compatible(const InstrumentItem& instrumentItem,
                                 const RealDataItem& realDataItem)
{
    return getRank(instrumentItem) == getRank(realDataItem);
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

//! Returns trues if [nxbin X nybin] of the detector is the same as in realData.

bool ImportDataUtils::HasSameShape(const InstrumentItem& instrumentItem,
                                   const RealDataItem& realDataItem, QString* message)
{
    if (!Compatible(instrumentItem, realDataItem))
        return false;

    bool isSame(true);

    auto dataShape = RealDataShape(realDataItem);
    auto detectorShape = DetectorShape(instrumentItem);

    if (dataShape != detectorShape) {
        isSame = false;
        if (message)
            *message = QString("detector [%1x%2], data [%3x%4]")
                      .arg(detectorShape.first).arg(detectorShape.second)
                      .arg(dataShape.first).arg(dataShape.second);
    }

    return isSame;
}

// TODO refactor this after appearance of specular instrument
void ImportDataUtils::SetInstrumentShapeToData(InstrumentItem& instrumentItem,
                                               const RealDataItem& realDataItemItem)
{
    auto dataShape = RealDataShape(realDataItemItem);
    if(auto offspecInstrument = dynamic_cast<OffSpecInstrumentItem*>(&instrumentItem)) {
        offspecInstrument->detectorItem()->setSize(dataShape.first, dataShape.second);
    } else if (auto gisasInstrument = dynamic_cast<GISASInstrumentItem*>(&instrumentItem)) {
        gisasInstrument->detectorItem()->setSize(dataShape.first, dataShape.second);
    } else {
        throw GUIHelpers::Error("ImportDataUtils::SetInstrumentShapeToData() -> Error."
                                "Not supported instrument type");
    }
}

namespace {
//! Returns shape of RealDataItem axes.

std::pair<int, int> RealDataShape(const RealDataItem& realData)
{
    std::pair<int, int> result;
    if (const auto intensityItem = realData.intensityDataItem()) {
        auto xaxis = intensityItem->getItem(IntensityDataItem::P_XAXIS);
        result.first = xaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        auto yaxis = intensityItem->getItem(IntensityDataItem::P_YAXIS);
        result.second = yaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    }
    return result;
}

//! Returns shape of Instrument's detector axes.

// TODO refactor this after appearance of specular instrument

std::pair<int, int> DetectorShape(const InstrumentItem& instrumentItem)
{
    if(auto offspecInstrument = dynamic_cast<const OffSpecInstrumentItem*>(&instrumentItem)) {
        std::unique_ptr<IDetector2D> detector = offspecInstrument->detectorItem()->createDetector();
        return std::make_pair(static_cast<int>(detector->getAxis(0).size()),
                              static_cast<int>(detector->getAxis(1).size()));

    } else if (auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(&instrumentItem)) {
        std::unique_ptr<IDetector2D> detector = gisasInstrument->detectorItem()->createDetector();
        return std::make_pair(static_cast<int>(detector->getAxis(0).size()),
                              static_cast<int>(detector->getAxis(1).size()));
    } else {
        throw GUIHelpers::Error("ImportDataUtils::DetectorShape() -> Error."
                                "Not supported instrument type");
    }

}

}
