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

BeamWavelengthItem::BeamWavelengthItem(const QString& model_type,const QString& distribution_group)
    : BeamDistributionItem(model_type, m_show_mean)
{
    register_distribution_group(distribution_group);

    SessionItem *valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_MEAN);
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

SpecularBeamWavelengthItem::SpecularBeamWavelengthItem()
    : BeamWavelengthItem(Constants::SpecularBeamWavelengthType,
                         Constants::SymmetricDistributionGroup)
{}
