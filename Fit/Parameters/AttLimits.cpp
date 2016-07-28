// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/AttLimits.cpp
//! @brief     Implements class AttLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AttLimits.h"
#include "Numeric.h"
#include <iomanip>
#include <iostream>


//! Creates an object which can have only positive values (>0., zero is not included)
AttLimits AttLimits::positive()
{
    return lowerLimited(Numeric::double_min);
}

//! Prints class
void AttLimits::print(std::ostream& ostr) const
{
    if(isFixed()) {
        ostr << "fixed";
    }else if(!hasLowerLimit() && !hasUpperLimit() ) {
        ostr << "free";
    } else if(hasLowerLimit() && !hasUpperLimit()) {
        ostr << "lim("  << std::fixed <<std::setprecision(2) << m_lower_limit << ",)";
    }else if(hasUpperLimit() && !hasLowerLimit()) {
        ostr << "lim(," << std::fixed <<std::setprecision(2) << m_upper_limit << ",)";
    }else if(hasLowerAndUpperLimits()) {
        ostr << "lim(" << std::fixed <<std::setprecision(2) << m_lower_limit << "," <<
            std::fixed <<std::setprecision(2) << m_upper_limit << ")";
    }
}

bool AttLimits::isInRange(double value) const
{
    if(hasLowerLimit() && value < m_lower_limit) return false;
    if(hasUpperLimit() && value >= m_upper_limit) return false;
    return true;
}

bool AttLimits::operator==(const AttLimits& other) const
{
    return (m_has_lower_limit == other.m_has_lower_limit) &&
            (m_has_upper_limit == other.m_has_upper_limit) &&
            (m_lower_limit == other.m_lower_limit) &&
            (m_upper_limit == other.m_upper_limit);
}
