// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BeamAngleItems.h"
#include "item_constants.h"

BeamInclinationAngleItem::BeamInclinationAngleItem(ParameterizedItem *parent)
    : BeamDistributionItem(Constants::BeamInclinationAngleType, parent)
{
    setItemName(Constants::BeamInclinationAngleType);
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.2);
    setPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(0.0, 90.0), 2));
}


BeamAzimuthalAngleItem::BeamAzimuthalAngleItem(ParameterizedItem *parent)
    : BeamDistributionItem(Constants::BeamAzimuthalAngleType, parent)
{
    setItemName(Constants::BeamAzimuthalAngleType);
    setRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE, 0.0);
    setPropertyAttribute(BeamDistributionItem::P_CACHED_VALUE, PropertyAttribute(PropertyAttribute::HIDDEN, AttLimits::limited(-90.0, 90.0), 2));
}

