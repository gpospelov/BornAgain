// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamWavelengthItem.cpp
//! @brief     Implements class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BeamWavelengthItem.h"

BeamWavelengthItem::BeamWavelengthItem()
    : BeamDistributionItem(Constants::BeamWavelengthType, m_show_mean)
{
    register_distribution_group(Constants::DistributionExtendedGroup);

    SessionItem *valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_VALUE);
    valueItem->setLimits(RealLimits::positive());
    valueItem->setDecimals(4);
    valueItem->setValue(0.1);

    initDistributionItem(m_show_mean);
}

//! Returns wavelength. In the case of distribution applied, returns its mean.

double BeamWavelengthItem::wavelength() const
{
    return BeamDistributionItem::meanValue();
}
