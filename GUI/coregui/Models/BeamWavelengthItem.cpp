// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
    setItemValue(BeamDistributionItem::P_CACHED_VALUE, 0.1);
}
