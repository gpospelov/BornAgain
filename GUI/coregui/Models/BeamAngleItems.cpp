// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamAngleItems.cpp
//! @brief     Implements class BeamAngleItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "BeamAngleItems.h"
#include "Units.h"

BeamAzimuthalAngleItem::BeamAzimuthalAngleItem()
    : BeamDistributionItem(Constants::BeamAzimuthalAngleType)
{
    register_distribution_group();

    SessionItem *valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_VALUE);
    valueItem->setLimits(RealLimits::limited(-90.0, 90.0));
    valueItem->setDecimals(3);
    valueItem->setValue(0.0);

    initDistributionItem();
}

//! Returns beam azimuthal angle. In the case of distribution applied, returns its mean.

double BeamAzimuthalAngleItem::azimuthalAngle() const
{
    return BeamDistributionItem::meanValue();
}

double BeamAzimuthalAngleItem::scaleFactor() const
{
    return Units::degree;
}

// ------------------------------------------------------------------------------------------------

BeamInclinationAngleItem::BeamInclinationAngleItem()
    : BeamDistributionItem(Constants::BeamInclinationAngleType)
{
    register_distribution_group();

    SessionItem *valueItem = getGroupItem(P_DISTRIBUTION)->getItem(DistributionNoneItem::P_VALUE);
    valueItem->setLimits(RealLimits::limited(0.0, 90.0));
    valueItem->setDecimals(3);
    valueItem->setValue(0.2);

    initDistributionItem();
}

//! Returns beam inclination angle. In the case of distribution applied, returns its mean.

double BeamInclinationAngleItem::inclinationAngle() const
{
    return BeamDistributionItem::meanValue();
}

double BeamInclinationAngleItem::scaleFactor() const
{
    return Units::degree;
}

