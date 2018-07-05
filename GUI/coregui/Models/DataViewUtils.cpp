#include "DataViewUtils.h"
#include "ComboProperty.h"
#include "DataItem1DView.h"
#include "DomainObjectBuilder.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "IUnitConverter.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "SessionModel.h"

namespace {
const QMap<QString, AxesUnits> unit_from_names = {{Constants::UnitsNbins, AxesUnits::NBINS},
                                                  {Constants::UnitsRadians, AxesUnits::RADIANS},
                                                  {Constants::UnitsDegrees, AxesUnits::DEGREES},
                                                  {Constants::UnitsMm, AxesUnits::MM},
                                                  {Constants::UnitsQyQz, AxesUnits::QSPACE}};

const QMap<AxesUnits, QString> names_from_units = {{AxesUnits::NBINS, Constants::UnitsNbins},
                                                   {AxesUnits::RADIANS, Constants::UnitsRadians},
                                                   {AxesUnits::MM, Constants::UnitsMm},
                                                   {AxesUnits::QSPACE, Constants::UnitsQyQz},
                                                   {AxesUnits::DEGREES, Constants::UnitsDegrees}};

JobItem* parentJobItem(SessionItem* item)
{
    assert(item);
    do {
        if (item->modelType() == Constants::JobItemType)
            return dynamic_cast<JobItem*>(item);
    } while ((item = item->parent()));
    throw GUIHelpers::Error("Error in parentJobItem: passed item is not owned by any job item");
}

ComboProperty availableUnits(const IUnitConverter* converter)
{
    assert(converter);

    ComboProperty result;
    for (auto units : converter->availableUnits())
        result << names_from_units[units];

    result.setValue(names_from_units[converter->defaultUnits()]);
    return result;
}

void updateAxesTitle(DataItem1DView* view_item, const IUnitConverter* converter,
                     AxesUnits units)
{
    view_item->setXaxisTitle(QString::fromStdString(converter->axisName(0, units)));
    if (converter->dimension() > 1)
        view_item->setYaxisTitle(QString::fromStdString(converter->axisName(1, units)));
}
}

void DataViewUtils::initDataView(JobItem* jobItem)
{
    assert(jobItem->isValidForFitting());
    assert(jobItem->instrumentItem()->modelType() == Constants::SpecularInstrumentType);
    assert(!jobItem->getItem(JobItem::T_DATAVIEW));

    SessionModel* model = jobItem->model();
    auto view_item = dynamic_cast<DataItem1DView*>(model->insertNewItem(
        Constants::DataItem1DViewType, jobItem->index(), -1, JobItem::T_DATAVIEW));

    assert(view_item);
    setUnitProperties(view_item);

    view_item->addItem(jobItem->realDataItem()->dataItem());
    view_item->addItem(jobItem->dataItem());
}

void DataViewUtils::setUnitProperties(DataItem1DView* view_item)
{
    auto job_item = parentJobItem(view_item);
    assert(job_item);

    auto converter = DomainObjectBuilder::createUnitConverter(job_item->instrumentItem());
    view_item->setItemValue(DataItem1DView::P_AXES_UNITS,
                            availableUnits(converter.get()).variant());
    updateAxesTitle(view_item, converter.get(), converter->defaultUnits());
}
