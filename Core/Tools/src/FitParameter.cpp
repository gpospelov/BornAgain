#include "FitParameter.h"
#include <iostream>
#include <iomanip>

FitParameter::FitParameter() : m_value(0), m_step(0), m_error(0)
{

}


FitParameter::FitParameter(const std::string &name, double value, double step, const AttLimits &attlimits)
    : INamed(name)
    , AttLimits(attlimits)
    , m_value(value)
    , m_step(step)
    , m_error(0.0)
{

}


void FitParameter::print(std::ostream &ostr) const
{
    const int w(40);
    std::string adjusted_name = getName();
    adjusted_name.resize(w,' ');
    ostr << std::setw(w) << adjusted_name << std::scientific << std::setprecision(8) << m_value << "  ";
    AttLimits::print(ostr);
}
