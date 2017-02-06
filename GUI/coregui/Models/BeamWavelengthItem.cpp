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
    SessionItem *distribution = dynamic_cast<DistributionNoneItem *>(getGroupItem(P_DISTRIBUTION));
    Q_ASSERT(distribution);
    auto value = distribution->getItem(DistributionNoneItem::P_VALUE);
    value->setLimits(RealLimits::positive());
    value->setDecimals(4);
    value->setValue(0.1);
}

//! Returns wavelength. In the case of distribution applied, returns its mean.

double BeamWavelengthItem::wavelength() const
{
    return this->meanValue();
}
