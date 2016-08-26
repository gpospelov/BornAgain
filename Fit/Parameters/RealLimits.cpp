// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/Limits.cpp
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

//! Creates an object which can have only positive values (>0., zero is not included)
RealLimits RealLimits::positive()
{
    return lowerLimited(std::numeric_limits<double>::min());
}

//! Prints class
void RealLimits::print(std::ostream& ostr) const
{
    if      (!hasLowerLimit() && !hasUpperLimit())
        ostr << "unlimited";
    else if (hasLowerLimit() && !hasUpperLimit())
        ostr << "lim("  << std::fixed <<std::setprecision(2) << m_lower_limit << ",)";
    else if (hasUpperLimit() && !hasLowerLimit())
        ostr << "lim(," << std::fixed <<std::setprecision(2) << m_upper_limit << ",)";
    else if (hasLowerAndUpperLimits())
        ostr << "lim(" << std::fixed <<std::setprecision(2) << m_lower_limit << "," <<
            std::fixed <<std::setprecision(2) << m_upper_limit << ")";
}

bool RealLimits::isInRange(double value) const
{
    if(hasLowerLimit() && value < m_lower_limit) return false;
    if(hasUpperLimit() && value >= m_upper_limit) return false;
    return true;
}

bool RealLimits::operator==(const RealLimits& other) const
{
    return (m_has_lower_limit == other.m_has_lower_limit) &&
            (m_has_upper_limit == other.m_has_upper_limit) &&
            (m_lower_limit == other.m_lower_limit) &&
            (m_upper_limit == other.m_upper_limit);
}
