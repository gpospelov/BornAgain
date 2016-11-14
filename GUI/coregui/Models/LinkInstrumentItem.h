// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LinkInstrumentItem.h
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

#ifndef LINKINSTRUMENTITEM_H
#define LINKINSTRUMENTITEM_H

#include "SessionItem.h"

//! The LinkInstrumentItem class is a helper item to link RealDataItem to InstrumentItem.
//! Contains dynamic ComboProperty with list of all instrument names, which is updated on
//! every change of instrument name, and on add/remove InstrumentItem.
//! Handled by temporary (not serializable) model from LinkInstrumentManager.

class BA_CORE_API_ LinkInstrumentItem : public SessionItem
{
public:
    static const QString P_REALDATA_NAME;
    static const QString P_INSTRUMENT_ID;
    static const QString P_INSTRUMENT_NAME;
    static const QString P_INSTRUMENT_COMBO;
    LinkInstrumentItem();
};

#endif // LINKINSTRUMENTITEM_H
