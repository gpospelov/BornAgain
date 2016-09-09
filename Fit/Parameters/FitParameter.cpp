// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameter.cpp
//! @brief     Implements class FitParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameter.h"
#include <iomanip>
#include <sstream>

FitParameter::FitParameter() : m_start_value(0), m_value(0), m_step(0), m_error(0)
{}

FitParameter::FitParameter(
    const std::string& name, double value, double step, const RealLimits& limits,
    const Attributes& attr, double error)
    : RealLimits(limits)
    , Attributes(attr)
    , m_name(name)
    , m_start_value(value)
    , m_value(value)
    , m_step(step)
    , m_error(error)
{}

std::string FitParameter::limitsToString() const
{
    std::ostringstream result;

    if(isFixed()) {
        result << "fixed";
    }else if(!hasLowerLimit() && !hasUpperLimit() ) {
        result << "free";
    } else if(hasLowerLimit() && !hasUpperLimit()) {
        result << "lim("  << std::fixed <<std::setprecision(2) << m_lower_limit << ",)";
    }else if(hasUpperLimit() && !hasLowerLimit()) {
        result << "lim(," << std::fixed <<std::setprecision(2) << m_upper_limit << ",)";
    }else if(hasLowerAndUpperLimits()) {
        result << "lim(" << std::fixed <<std::setprecision(2) << m_lower_limit << "," <<
            std::fixed <<std::setprecision(2) << m_upper_limit << ")";
    }

    return result.str();
}

void FitParameter::print(std::ostream& ostr) const
{
    const int max_length_of_name(40);
    std::string adjusted_name = m_name;
    adjusted_name.resize(max_length_of_name,' ');
    ostr << adjusted_name << std::scientific << std::setprecision(8) << m_value << "  ";
    Attributes::print(ostr);
    ostr << " ";
    RealLimits::print(ostr);
}
