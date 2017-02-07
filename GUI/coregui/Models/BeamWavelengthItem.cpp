// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamWavelengthItem.cpp
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
    register_distribution_group();

    SessionItem *valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_VALUE);
    valueItem->setLimits(RealLimits::positive());
    valueItem->setDecimals(4);
    valueItem->setValue(0.1);

    initDistributionItem();
}

//! Returns wavelength. In the case of distribution applied, returns its mean.

double BeamWavelengthItem::wavelength() const
{
    return this->meanValue();
}
