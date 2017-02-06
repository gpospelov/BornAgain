//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealLimitsItems.h
//! @brief     Defines RealLimitsItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealLimitsItems.h"

const QString RealLimitsItem::P_XMIN = "Min";
const QString RealLimitsItem::P_XMAX = "Max";

RealLimitsItem::RealLimitsItem(const QString& name)
    : SessionItem(name)
{

}

LimitlessItem::LimitlessItem()
    : RealLimitsItem(Constants::RealLimitsLimitlessType)
{

}

RealLimits LimitlessItem::createRealLimits() const
{
    return RealLimits();
}

PositiveItem::PositiveItem()
    : RealLimitsItem(Constants::RealLimitsPositiveType)
{

}

RealLimits PositiveItem::createRealLimits() const
{
    return RealLimits::positive();
}

LimitedItem::LimitedItem()
    : RealLimitsItem(Constants::RealLimitsLimitedType)
{
    addProperty(P_XMIN, 0.0)->setToolTip("Minimum allowed value");
    addProperty(P_XMAX, 1.0)->setToolTip("Maximum allowed value");
}

RealLimits LimitedItem::createRealLimits() const
{
    return RealLimits::limited(getItemValue(P_XMIN).toDouble(), getItemValue(P_XMAX).toDouble());
}
