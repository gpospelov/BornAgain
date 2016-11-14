// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataItem.cpp
//! @brief     Implements class RealDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataItem.h"
#include "GUIHelpers.h"
#include "IntensityDataItem.h"
#include "ComboProperty.h"
#include "SessionModel.h"
#include "ComboProperty.h"
#include "JobItemHelper.h"
#include "ImportDataAssistant.h"
#include "MaskUnitsConverter.h"
#include "JobItemFunctions.h"
#include <QDebug>

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

    mapper()->setOnChildPropertyChange(
                [this](SessionItem* item, const QString &name)
    {
        if (item && item->modelType() == Constants::IntensityDataType
            && name == IntensityDataItem::P_AXES_UNITS) {
            if(!m_linkedInstrument)
                return;
            mapper()->setActive(false);

            MaskUnitsConverter converter;
            converter.convertToNbins(intensityDataItem());

            JobItemHelper::updateDataAxes(intensityDataItem(), m_linkedInstrument);

            converter.convertFromNbins(intensityDataItem());

            mapper()->setActive(true);
        }
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

//! Sets OutputData to underlying item. Creates it, if not exists.

void RealDataItem::setOutputData(OutputData<double> *data)
{
    IntensityDataItem *item = intensityDataItem();
    Q_ASSERT(item);
    item->setOutputData(data);
}

void RealDataItem::linkToInstrument(const InstrumentItem *instrument)
{
    m_linkedInstrument = instrument;
    updateToInstrument();
}

//! Updates the name of file to store intensity data.

void RealDataItem::updateIntensityDataFileName()
{
    if(IntensityDataItem *item = intensityDataItem())
        item->setItemValue(IntensityDataItem::P_FILE_NAME,
                           JobItemFunctions::realDataFileName(*this));
}

void RealDataItem::updateToInstrument()
{
    if(!intensityDataItem())
        return;

    if(!intensityDataItem()->getOutputData())
        return;

    IntensityDataItem *item = intensityDataItem();
    Q_ASSERT(item);

    if(m_linkedInstrument == 0) {
        ComboProperty combo;
        combo << Constants::UnitsNbins;
        item->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
        item->getItem(IntensityDataItem::P_AXES_UNITS)->setVisible(true);
        item->setXaxisTitle("X [nbins]");
        item->setYaxisTitle("Y [nbins]");
        MaskUnitsConverter converter;
        converter.convertToNbins(intensityDataItem());
        item->setOutputData(ImportDataAssistant::createSimlifiedOutputData(*item->getOutputData()));
        item->setAxesRangeToData();
        converter.convertFromNbins(intensityDataItem());
    }

    else {
        JobItemHelper::adjustAxesUnitsToInstrument(item, m_linkedInstrument);
    }

}
