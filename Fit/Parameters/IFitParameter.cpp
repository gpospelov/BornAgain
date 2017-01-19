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

#include "IFitParameter.h"
#include <iomanip>
#include <sstream>

IFitParameter::IFitParameter()
    : m_start_value(0.0)
    , m_value(0.0)
    , m_step(0.0)
    , m_error(0.0)
{

}

IFitParameter::IFitParameter(const std::string &name, double value, const AttLimits &limits,
                                 double step)
    : m_name(name)
    , m_start_value(value)
    , m_value(value)
    , m_step(step)
    , m_error(0.0)
    , m_limits(limits)
{

}

IFitParameter *IFitParameter::clone() const
{
    return new IFitParameter(*this);
}

std::string IFitParameter::name() const { return m_name; }

IFitParameter& IFitParameter::setName(const std::string& name)
{
    m_name = name;
    return *this;
}

double IFitParameter::startValue() const { return m_start_value; }

double IFitParameter::value() const { return m_value; }

void IFitParameter::setValue(double value) { m_value = value; }

double IFitParameter::step() const { return m_step; }

IFitParameter &IFitParameter::setStep(double value)
{
    m_step = value;
    return *this;
}

double IFitParameter::error() const { return m_error; }

void IFitParameter::setError(double value) { m_error = value; }

const AttLimits &IFitParameter::limits() const { return m_limits;}

AttLimits &IFitParameter::limits() { return m_limits;}

IFitParameter& IFitParameter::setLimits(const AttLimits &limits)
{
    m_limits = limits;
    return *this;
}

IFitParameter &IFitParameter::setLowerLimited(double bound_value)
{
    m_limits = AttLimits::lowerLimited(bound_value);
    return *this;
}

IFitParameter &IFitParameter::setPositive()
{
    m_limits = AttLimits::positive();
    return *this;
}

IFitParameter &IFitParameter::setNonnegative()
{
    m_limits = AttLimits::nonnegative();
    return *this;
}

IFitParameter &IFitParameter::setUpperLimited(double bound_value)
{
    m_limits = AttLimits::upperLimited(bound_value);
    return *this;
}

IFitParameter &IFitParameter::setLimited(double left_bound_value, double right_bound_value)
{
    m_limits = AttLimits::limited(left_bound_value, right_bound_value);
    return *this;
}

IFitParameter &IFitParameter::setFixed()
{
    m_limits = AttLimits::fixed();
    return *this;
}

std::string IFitParameter::toString() const
{
    std::ostringstream ostr;

    const int max_length_of_name(10);
    std::string adjusted_name = m_name;
    adjusted_name.resize(max_length_of_name,' ');
    ostr << adjusted_name << std::scientific << std::setprecision(8) << m_value << "  ";
    ostr << m_limits.toString();
    return ostr.str();
}

IFitParameter::IFitParameter(const IFitParameter &other)
{
    m_name = other.m_name;
    m_start_value = other.m_start_value;
    m_value = other.m_value;
    m_step = other.m_step;
    m_error = other.m_error;
    m_limits = other.m_limits;
}
