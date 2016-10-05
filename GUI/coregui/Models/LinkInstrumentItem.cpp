// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LinkInstrumentItem.cpp
//! @brief     Defines class LinkInstrumentItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LinkInstrumentItem.h"
#include "ComboProperty.h"

const QString LinkInstrumentItem::P_REALDATA_NAME = "RealDataName";
const QString LinkInstrumentItem::P_INSTRUMENT_ID = "Instrument Id";
const QString LinkInstrumentItem::P_INSTRUMENT_NAME = "Instrument";
const QString LinkInstrumentItem::P_INSTRUMENT_COMBO = "Combo";


LinkInstrumentItem::LinkInstrumentItem()
    : SessionItem(Constants::LinkInstrumentType)
{
    addProperty(P_REALDATA_NAME, QString());
    addProperty(P_INSTRUMENT_ID, QString());
    addProperty(P_INSTRUMENT_NAME, QString());
    ComboProperty instruments = ComboProperty() << "Undefined";
    addProperty(P_INSTRUMENT_COMBO, instruments.getVariant());
}
