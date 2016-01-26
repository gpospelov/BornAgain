// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/InstrumentItem.cpp
//! @brief     Implements class InstrumentItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InstrumentItem.h"
#include "DetectorItems.h"
#include "BeamItem.h"

InstrumentItem::InstrumentItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::InstrumentType, parent)
{
    registerProperty(P_NAME, Constants::InstrumentType);
    addToValidChildren(Constants::BeamType);
    addToValidChildren(Constants::DetectorType);
}

BeamItem *InstrumentItem::getBeamItem()
{
    for(ParameterizedItem *item : childItems()) {
        if(item->modelType() == Constants::BeamType) {
            return dynamic_cast<BeamItem *>(item);
        }
    }
    return 0;
}

DetectorItem *InstrumentItem::getDetectorItem()
{
    for(ParameterizedItem *item : childItems()) {
        if(item->modelType() == Constants::DetectorType) {
            return dynamic_cast<DetectorItem *>(item);
        }
    }
    return 0;
}
