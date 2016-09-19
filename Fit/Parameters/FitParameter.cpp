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

// --------------------------------------------------------------------------------

NewFitParameter::NewFitParameter()
    : m_start_value(0.0)
    , m_value(0.0)
    , m_step(0.0)
    , m_error(0.0)
{

}

NewFitParameter::NewFitParameter(const std::string &name, double value, const AttLimits &limits,
                                 double step)
    : m_name(name)
    , m_start_value(value)
    , m_value(value)
    , m_step(step)
    , m_error(0.0)
    , m_limits(limits)
{

}

std::string NewFitParameter::name() const { return m_name; }

double NewFitParameter::startValue() const { return m_start_value; }

double NewFitParameter::value() const { return m_value; }

void NewFitParameter::setValue(double value) { m_value = value; }

double NewFitParameter::step() const { return m_step; }

NewFitParameter &NewFitParameter::setStep(double value)
{
    m_step = value;
    return *this;
}

double NewFitParameter::error() const { return m_error; }

void NewFitParameter::setError(double value) { m_error = value; }

const AttLimits &NewFitParameter::limits() const { return m_limits;}

AttLimits &NewFitParameter::limits() { return m_limits;}

NewFitParameter& NewFitParameter::setLimits(const AttLimits &limits)
{
    m_limits = limits;
    return *this;
}

NewFitParameter &NewFitParameter::lowerLimited(double bound_value)
{
    m_limits = AttLimits::lowerLimited(bound_value);
    return *this;
}

NewFitParameter &NewFitParameter::positive()
{
    m_limits = AttLimits::positive();
    return *this;
}

NewFitParameter &NewFitParameter::nonnegative()
{
    m_limits = AttLimits::nonnegative();
    return *this;
}

NewFitParameter &NewFitParameter::upperLimited(double bound_value)
{
    m_limits = AttLimits::upperLimited(bound_value);
    return *this;
}

NewFitParameter &NewFitParameter::limited(double left_bound_value, double right_bound_value)
{
    m_limits = AttLimits::limited(left_bound_value, right_bound_value);
    return *this;
}

NewFitParameter &NewFitParameter::fixed()
{
    m_limits = AttLimits::fixed();
    return *this;
}


