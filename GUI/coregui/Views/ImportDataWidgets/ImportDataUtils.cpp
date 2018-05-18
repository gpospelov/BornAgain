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
const QString filter_string = "Intensity File (*.int *.gz *.tif *.tiff *.txt);;"
                              "Other (*)";

int getRank(const RealDataItem& item)
{
    Q_UNUSED(item); // to be extended
    return 2;
}

int getRank(const InstrumentItem& item) {
    if (item.modelType() == Constants::GISASInstrumentType
        || item.modelType() == Constants::OffSpecInstrumentType)
        return 2;
    return -1;
}

std::pair<int, int> RealDataShape(const RealDataItem& realData);

std::pair<int, int> DetectorShape(const InstrumentItem& instrumentItem);
std::pair<int, int> DetectorShape(const GISASInstrumentItem& instrumentItem);
std::pair<int, int> DetectorShape(const OffSpecInstrumentItem& instrumentItem);

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

std::unique_ptr<OutputData<double>>
ImportDataUtils::CreateSimplifiedOutputData(const OutputData<double>& data)
{
    const size_t data_rank = data.getRank();
    if (data_rank > 2 || data_rank < 1)
        throw std::runtime_error("Error in ImportDataUtils::CreateSimplifiedOutputData: passed "
                                 "array is neither 1D nor 2D");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < data_rank; ++i) {
        const IAxis& axis = data.getAxis(i);
        const size_t axis_size = axis.size();
        const double min = 0.0;
        const double max = axis_size;
        result->addAxis(FixedBinAxis(axis.getName(), axis_size, min, max));
    }
    result->setRawDataVector(data.getRawDataVector());

    return result;
}

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

// TODO refactor DetectorShape functions after specular instrument emergence

std::pair<int, int> DetectorShape(const InstrumentItem& instrumentItem)
{
    if (const auto offspecInstrument = dynamic_cast<const OffSpecInstrumentItem*>(&instrumentItem))
        return DetectorShape(*offspecInstrument);
    else if (const auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(&instrumentItem))
        return DetectorShape(*gisasInstrument);
    else
        throw GUIHelpers::Error("ImportDataUtils::DetectorShape() -> Error."
                                "Not supported instrument type");
}

std::pair<int, int> DetectorShape(const GISASInstrumentItem& instrumentItem)
{
    std::unique_ptr<IDetector2D> detector = instrumentItem.detectorItem()->createDetector();
    return std::make_pair(static_cast<int>(detector->getAxis(0).size()),
                          static_cast<int>(detector->getAxis(1).size()));
}

std::pair<int, int> DetectorShape(const OffSpecInstrumentItem& instrumentItem)
{
    const int alpha_nbins = instrumentItem.getItem(OffSpecInstrumentItem::P_ALPHA_AXIS)
                                ->getItemValue(BasicAxisItem::P_NBINS).toInt();
    std::unique_ptr<IDetector2D> detector = instrumentItem.detectorItem()->createDetector();
    return std::make_pair(alpha_nbins, static_cast<int>(detector->getAxis(1).size()));
}

}
