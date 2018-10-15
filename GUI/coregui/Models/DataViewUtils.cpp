#include "DataViewUtils.h"
#include "ComboProperty.h"
#include "DataItem.h"
#include "Data1DViewItem.h"
#include "DomainObjectBuilder.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "IUnitConverter.h"
#include "JobItem.h"
#include "OutputData.h"
#include "DataPropertyContainer.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include "UnitConverterUtils.h"

namespace {
const QMap<QString, AxesUnits> units_from_names{{Constants::UnitsNbins, AxesUnits::NBINS},
                                                {Constants::UnitsRadians, AxesUnits::RADIANS},
                                                {Constants::UnitsDegrees, AxesUnits::DEGREES},
                                                {Constants::UnitsMm, AxesUnits::MM},
                                                {Constants::UnitsQyQz, AxesUnits::QSPACE}};

const QMap<AxesUnits, QString> names_from_units{{AxesUnits::NBINS, Constants::UnitsNbins},
                                                {AxesUnits::RADIANS, Constants::UnitsRadians},
                                                {AxesUnits::MM, Constants::UnitsMm},
                                                {AxesUnits::QSPACE, Constants::UnitsQyQz},
                                                {AxesUnits::DEGREES, Constants::UnitsDegrees}};

std::unique_ptr<IUnitConverter> getConverter(Data1DViewItem* view_item)
{
    auto job_item = view_item->jobItem();
    assert(job_item->instrumentItem());

    return DomainObjectBuilder::createUnitConverter(job_item->instrumentItem());
}

AxesUnits selectedUnits(Data1DViewItem* view_item)
{
    auto current_unit_name
        = view_item->getItemValue(Data1DViewItem::P_AXES_UNITS).value<ComboProperty>().getValue();
    return units_from_names[current_unit_name];
}
}

void DataViewUtils::updateAxesTitle(Data1DViewItem* view_item)
{
    auto converter = getConverter(view_item);
    auto current_units = selectedUnits(view_item);
    view_item->setXaxisTitle(QString::fromStdString(converter->axisName(0, current_units)));
    if (converter->dimension() > 1)
        view_item->setYaxisTitle(QString::fromStdString(converter->axisName(1, current_units)));
}

std::unique_ptr<OutputData<double>> DataViewUtils::getTranslatedData(Data1DViewItem* view_item,
                                                                     DataItem* data_item)
{
    std::unique_ptr<OutputData<double>> result;
    if (!data_item || !data_item->getOutputData())
        return result;

    auto converter = getConverter(view_item);
    auto current_units = selectedUnits(view_item);

    result = UnitConverterUtils::createOutputData(*converter, current_units);
    result->setRawDataVector(data_item->getOutputData()->getRawDataVector());

    return result;
}
