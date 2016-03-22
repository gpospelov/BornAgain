// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/InstrumentItem.h
//! @brief     Defines class InstrumentItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENT_ITEM_H
#define INSTRUMENT_ITEM_H

#include "SessionItem.h"

class BeamItem;
class DetectorItem;

class BA_CORE_API_ InstrumentItem : public SessionItem
{
    

public:
    explicit InstrumentItem();
    virtual ~InstrumentItem() {}

    BeamItem *getBeamItem();

    DetectorItem *getDetectorItem();
};

#endif
