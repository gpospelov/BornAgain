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
#include "IntensityDataItem.h"
#include "ComboProperty.h"
#include "SessionModel.h"
#include "ComboProperty.h"
#include "JobItemUtils.h"
#include "ImportDataUtils.h"
#include "MaskUnitsConverter.h"
#include "JobItemFunctions.h"
#include "InstrumentItems.h"

const QString RealDataItem::P_INSTRUMENT_ID = "Instrument Id";
const QString RealDataItem::P_INSTRUMENT_NAME = "Instrument";
const QString RealDataItem::T_INTENSITY_DATA = "Intensity data";

RealDataItem::RealDataItem()
    : SessionItem(Constants::RealDataType)
    , m_linkedInstrument(0)
{
    setItemName(QStringLiteral("undefined"));

    addProperty(P_INSTRUMENT_ID, QString());
    addProperty(P_INSTRUMENT_NAME, QString());

    registerTag(T_INTENSITY_DATA, 1, 1, QStringList() << Constants::IntensityDataType);
    setDefaultTag(T_INTENSITY_DATA);
    insertItem(0, new IntensityDataItem(), T_INTENSITY_DATA);

    mapper()->setOnPropertyChange(
        [this](const QString &name){
        if(name == P_NAME && isTag(T_INTENSITY_DATA)) {
            updateIntensityDataFileName();
        }

    }
    );

    mapper()->setOnChildrenChange(
        [this](SessionItem *item){
        if(item && item->modelType() == Constants::IntensityDataType)
            updateIntensityDataFileName();
        }
    );

    mapper()->setOnChildPropertyChange([this](SessionItem* item, const QString& name) {
        auto data_item = dynamic_cast<DataItem*>(item);
        if (!data_item || !m_linkedInstrument || name != DataItem::P_AXES_UNITS)
            return;

        mapper()->setActive(false);
        data_item->updateAxesUnits(m_linkedInstrument);
        mapper()->setActive(true);
    });
}

IntensityDataItem *RealDataItem::intensityDataItem()
{
    return const_cast<IntensityDataItem *>(
                static_cast<const RealDataItem*>(this)->intensityDataItem());
}

const IntensityDataItem *RealDataItem::intensityDataItem() const
{
    const IntensityDataItem *result = dynamic_cast<const IntensityDataItem *>(
                getItem(T_INTENSITY_DATA));
    return result;
}

DataItem* RealDataItem::dataItem()
{
    return const_cast<DataItem*>(static_cast<const RealDataItem*>(this)->dataItem());
}

const DataItem* RealDataItem::dataItem() const
{
    const DataItem* result = dynamic_cast<const DataItem*>(getItem(T_INTENSITY_DATA));
    return result;
}

//! Sets OutputData to underlying item. Creates it, if not exists.

void RealDataItem::setOutputData(OutputData<double> *data)
{
    DataItem* item = dataItem();
    Q_ASSERT(item);
    item->setOutputData(data);
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

//! Updates the name of file to store intensity data.

void RealDataItem::updateIntensityDataFileName()
{
    if (DataItem* item = dataItem())
        item->setItemValue(DataItem::P_FILE_NAME, JobItemFunctions::realDataFileName(*this));
}

void RealDataItem::updateToInstrument()
{
    DataItem* item = dataItem();
    assert(item
           && "RealDataItem::updateToInstrument assertion failed: underlying data item doesn't "
              "exist");
    assert(item->getOutputData()
           && "RealDataItem::updateToInstrument assertion failed: underlying data item doesn't "
              "contain data");
    JobItemUtils::setIntensityItemAxesUnits(item, m_linkedInstrument);
}
