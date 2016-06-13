// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/AttLimits.cpp
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
#include <iomanip>

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
