// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/RealLimits.cpp
//! @brief     Implements class Limits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RealLimits.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace {

bool isNonnegative(const RealLimits& lim)
{
    return lim.hasLowerLimit() && !lim.hasUpperLimit() && lim.getLowerLimit() == 0.0;
}

bool isLowerLimited(const RealLimits& lim)
{
    return lim.hasLowerLimit() && !lim.hasUpperLimit();
}

bool isUpperLimited(const RealLimits& lim)
{
    return !lim.hasLowerLimit() && lim.hasUpperLimit();
}

}

//! Creates an object which can have only positive values (>0., zero is not included)
RealLimits RealLimits::positive()
{
    return lowerLimited(std::numeric_limits<double>::min());
}

std::string RealLimits::toString() const
{
    std::ostringstream result;

    if (isLimitless()) {
        result << "unlimited";
    }

    else if(isPositive()) {
        result << "positive";
    }

    else if(isNonnegative(*this)) {
        result << "nonnegative";
    }

    else if(isLowerLimited(*this)) {
        result << "lowerLimited("  << std::fixed <<std::setprecision(2) << getLowerLimit() << ")";
    }

    else if(isUpperLimited(*this)) {
        result << "upperLimited(" << std::fixed <<std::setprecision(2) << getUpperLimit() << ")";
    }

    else if(isLimited()) {
        result << "limited(" << std::fixed <<std::setprecision(2) << getLowerLimit() << "," <<
            std::fixed <<std::setprecision(2) << getUpperLimit() << ")";
    }

    return result.str();
}

bool RealLimits::isInRange(double value) const
{
    if (hasLowerLimit() && value < m_lower_limit)
        return false;
    if (hasUpperLimit() && value >= m_upper_limit)
        return false;
    return true;
}

bool RealLimits::operator==(const RealLimits& other) const
{
    return (m_has_lower_limit == other.m_has_lower_limit)
           && (m_has_upper_limit == other.m_has_upper_limit)
           && (m_lower_limit == other.m_lower_limit) && (m_upper_limit == other.m_upper_limit);
}

bool RealLimits::isLimitless() const
{
    return !hasLowerLimit() && !hasUpperLimit();
}

bool RealLimits::isPositive() const
{
    return hasLowerLimit() && !hasUpperLimit()
           && getLowerLimit() == std::numeric_limits<double>::min();
}

bool RealLimits::isLimited() const
{
    return hasLowerLimit() && hasUpperLimit();
}
