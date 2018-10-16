// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataItem.cpp
//! @brief     Implements class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataItem.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "InstrumentItems.h"
#include "ItemFileNameUtils.h"
#include "JobItemUtils.h"
#include "SessionModel.h"
#include "SpecularDataItem.h"
#include "ImportDataInfo.h"
#include "PointwiseAxisItem.h"
#include "PointwiseAxis.h"

namespace
{
ImportDataInfo composeDefaultData(std::unique_ptr<OutputData<double>> data, const IAxis* axis,
                                  const QString& units_label);
}

const QString RealDataItem::P_INSTRUMENT_ID = "Instrument Id";
const QString RealDataItem::P_INSTRUMENT_NAME = "Instrument";
const QString RealDataItem::T_INTENSITY_DATA = "Intensity data";
const QString RealDataItem::P_NATIVE_AXIS = "Native user data axis";
const QString RealDataItem::P_NATIVE_UNITS = "Native user data units";

RealDataItem::RealDataItem()
    : SessionItem(Constants::RealDataType)
    , m_linkedInstrument(nullptr)
{
    setItemName(QStringLiteral("undefined"));

    // Registering this tag even without actual data item to avoid troubles in copying RealDataItem
    registerTag(T_INTENSITY_DATA, 1, 1,
                QStringList() << Constants::IntensityDataType << Constants::SpecularDataType);
    setDefaultTag(T_INTENSITY_DATA);

    addProperty(P_INSTRUMENT_ID, QString());
    addProperty(P_INSTRUMENT_NAME, QString());

    addGroupProperty(P_NATIVE_AXIS, Constants::PointwiseAxisType);
    addProperty(P_NATIVE_UNITS, Constants::UnitsNbins)->setVisible(false);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_NAME && getItem(T_INTENSITY_DATA))
            updateIntensityDataFileName();
    });

    mapper()->setOnChildrenChange([this](SessionItem* item) {
        if (dynamic_cast<DataItem*>(item))
            updateIntensityDataFileName();
    });

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& name) {
        auto data_item = dynamic_cast<DataItem*>(item);
        if (!data_item || !m_linkedInstrument || name != DataItem::P_AXES_UNITS)
            return;

        mapper()->setActive(false);
        data_item->updateAxesUnits(m_linkedInstrument);
        mapper()->setActive(true);
    });
}

IntensityDataItem* RealDataItem::intensityDataItem()
{
    return const_cast<IntensityDataItem*>(
        static_cast<const RealDataItem*>(this)->intensityDataItem());
}

const IntensityDataItem* RealDataItem::intensityDataItem() const
{
    return dynamic_cast<const IntensityDataItem*>(dataItem());
}

DataItem* RealDataItem::dataItem()
{
    return const_cast<DataItem*>(static_cast<const RealDataItem*>(this)->dataItem());
}

const DataItem* RealDataItem::dataItem() const
{
    const DataItem* result = dynamic_cast<const DataItem*>(getItem(T_INTENSITY_DATA));
    if (!result)
        throw GUIHelpers::Error(
            "Error in RealDataItem::dataItem: underlying data item was not set.");
    return result;
}

//! Sets OutputData to underlying item. Creates it, if not exists.

void RealDataItem::setOutputData(OutputData<double>* data)
{
    assert(data && "Assertion failed in RealDataItem::setOutputData: passed data is nullptr");
    assert(data->getRank() < 3 && data->getRank() > 0);

    const QString& target_model_type
        = data->getRank() == 2 ? Constants::IntensityDataType
                               : data->getRank() == 1 ? Constants::SpecularDataType : "";
    auto data_item = getItem(T_INTENSITY_DATA);
    if (data_item && data_item->modelType() != target_model_type)
        throw GUIHelpers::Error("Error in RealDataItem::setOutputData: trying to set data "
                                "incompatible with underlying data item");
    if (!data_item) {
        this->model()->insertNewItem(target_model_type, this->index(), 0, T_INTENSITY_DATA);
        assert(getItem(T_INTENSITY_DATA)
               && "Assertion failed in RealDataItem::setOutputData: inserting data item failed.");
    }
    dataItem()->setOutputData(data);
}

void RealDataItem::initDataItem(size_t data_rank)
{
    assert(data_rank <=2 && data_rank > 0);
    const QString& target_model_type =
        data_rank == 2 ? Constants::IntensityDataType : Constants::SpecularDataType;
    auto data_item = getItem(T_INTENSITY_DATA);
    if (data_item && data_item->modelType() != target_model_type)
        throw GUIHelpers::Error("Error in RealDataItem::setOutputData: trying to set data "
                                "incompatible with underlying data item");
    if (!data_item)
        this->model()->insertNewItem(target_model_type, this->index(), 0, T_INTENSITY_DATA);
}

void RealDataItem::setImportData(ImportDataInfo data) {
    if (!data)
        return;

    initDataItem(data.dataRank());
    dataItem()->reset(data);

    QString units_name = data.unitsLabel();
    getItem(P_NATIVE_UNITS)->setValue(units_name);
    if (units_name != Constants::UnitsNbins) {
        auto custom_axis_item = dynamic_cast<PointwiseAxisItem*>(getItem(P_NATIVE_AXIS));
        custom_axis_item->setAxis(&data.intensityData()->getAxis(0));
    }
}

void RealDataItem::linkToInstrument(const InstrumentItem *instrument, bool make_update)
{
    m_linkedInstrument = instrument;
    if(make_update)
        updateToInstrument();
}

std::vector<int> RealDataItem::shape() const
{
    auto data_item = dataItem();
    if (!data_item) {
        assert(data_item);
        return {};
    }
    return data_item->shape();
}

QString RealDataItem::underlyingDataModel()
{
    return dataItem()->modelType();
}

MaskContainerItem* RealDataItem::maskContainerItem()
{
    if (auto intensity_data = intensityDataItem())
        return intensity_data->maskContainerItem();
    return nullptr;
}

//! Updates the name of file to store intensity data.

void RealDataItem::updateIntensityDataFileName()
{
    if (DataItem* item = dataItem())
        item->setItemValue(DataItem::P_FILE_NAME, ItemFileNameUtils::realDataFileName(*this));
}

void RealDataItem::updateToInstrument()
{
    if (DataItem* data_item = dataItem()) {
        if (!m_linkedInstrument) {
            auto default_data = composeDefaultData(
                std::unique_ptr<OutputData<double>>(dataItem()->getOutputData()->clone()),
                item<PointwiseAxisItem>(P_NATIVE_AXIS).getAxis(),
                getItemValue(P_NATIVE_UNITS).toString());
            data_item->reset(default_data);
        } else
            JobItemUtils::setIntensityItemAxesUnits(data_item, m_linkedInstrument);
    }
}

namespace
{
ImportDataInfo composeDefaultData(std::unique_ptr<OutputData<double>> data, const IAxis* axis,
                                  const QString& units_label)
{
    if (units_label == Constants::UnitsNbins)
        return ImportDataInfo(std::move(data), units_label);

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(*axis);
    result->setRawDataVector(data->getRawDataVector());
    return ImportDataInfo(std::move(result), units_label);
}
}
