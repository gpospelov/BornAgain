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

#include "BeamWavelengthItem.h"

BeamWavelengthItem::BeamWavelengthItem()
    : BeamDistributionItem(Constants::BeamWavelengthType)
{
    SessionItem *cache = getItem(BeamDistributionItem::P_CACHED_VALUE);
    cache->setVisible(false);
    cache->setLimits(AttLimits::lowerLimited(1e-4));
    cache->setDecimals(4);
    setChildValue(BeamDistributionItem::P_CACHED_VALUE, 0.1);
}
