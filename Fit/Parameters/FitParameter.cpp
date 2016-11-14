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

FitParameter::FitParameter()
    : m_start_value(0.0)
    , m_value(0.0)
    , m_step(0.0)
    , m_error(0.0)
{

}

FitParameter::FitParameter(const std::string &name, double value, const AttLimits &limits,
                                 double step)
    : m_name(name)
    , m_start_value(value)
    , m_value(value)
    , m_step(step)
    , m_error(0.0)
    , m_limits(limits)
{

}

FitParameter *FitParameter::clone() const
{
    return new FitParameter(*this);
}

std::string FitParameter::name() const { return m_name; }

double FitParameter::startValue() const { return m_start_value; }

double FitParameter::value() const { return m_value; }

void FitParameter::setValue(double value) { m_value = value; }

double FitParameter::step() const { return m_step; }

FitParameter &FitParameter::setStep(double value)
{
    m_step = value;
    return *this;
}

double FitParameter::error() const { return m_error; }

void FitParameter::setError(double value) { m_error = value; }

const AttLimits &FitParameter::limits() const { return m_limits;}

AttLimits &FitParameter::limits() { return m_limits;}

FitParameter& FitParameter::setLimits(const AttLimits &limits)
{
    m_limits = limits;
    return *this;
}

FitParameter &FitParameter::setLowerLimited(double bound_value)
{
    m_limits = AttLimits::lowerLimited(bound_value);
    return *this;
}

FitParameter &FitParameter::setPositive()
{
    m_limits = AttLimits::positive();
    return *this;
}

FitParameter &FitParameter::setNonnegative()
{
    m_limits = AttLimits::nonnegative();
    return *this;
}

FitParameter &FitParameter::setUpperLimited(double bound_value)
{
    m_limits = AttLimits::upperLimited(bound_value);
    return *this;
}

FitParameter &FitParameter::setLimited(double left_bound_value, double right_bound_value)
{
    m_limits = AttLimits::limited(left_bound_value, right_bound_value);
    return *this;
}

FitParameter &FitParameter::setFixed()
{
    m_limits = AttLimits::fixed();
    return *this;
}

std::string FitParameter::toString() const
{
    std::ostringstream ostr;

    const int max_length_of_name(40);
    std::string adjusted_name = m_name;
    adjusted_name.resize(max_length_of_name,' ');
    ostr << adjusted_name << std::scientific << std::setprecision(8) << m_value << "  ";
    ostr << m_limits.toString();
    return ostr.str();
}

FitParameter::FitParameter(const FitParameter &other) : IFitParameter()
{
    m_name = other.m_name;
    m_start_value = other.m_start_value;
    m_value = other.m_value;
    m_step = other.m_step;
    m_error = other.m_error;
    m_limits = other.m_limits;
}
