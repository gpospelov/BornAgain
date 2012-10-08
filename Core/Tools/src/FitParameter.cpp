#include "FitParameter.h"
#include <iostream>


FitParameter::FitParameter() : m_value(0), m_step(0), m_error(0),
    m_has_lower_limit(false), m_has_upper_limit(false), m_lower_limit(0), m_upper_limit(0)
{
    setName("FitParameter");
}

FitParameter::FitParameter(const std::string &name, double value, double step, double error) : INamed(name), m_value(value), m_step(step), m_error(error),
    m_has_lower_limit(false), m_has_upper_limit(false), m_lower_limit(0), m_upper_limit(0)
{

}


FitParameter::FitParameter(const FitParameter &other) : INamed(other)
{
    setName("FitParameter");
    m_value = other.m_value;
    m_step = other.m_step;
    m_error = other.m_error;
    m_has_lower_limit = other.m_has_lower_limit;
    m_has_upper_limit = other.m_has_upper_limit;
    m_lower_limit = other.m_lower_limit;
    m_upper_limit = other.m_upper_limit;
}


FitParameter &FitParameter::operator=(const FitParameter &other)
{
    if( this != &other)
    {
        INamed::operator=(other);
        m_value = other.m_value;
        m_step = other.m_step;
        m_error = other.m_error;
        m_has_lower_limit = other.m_has_lower_limit;
        m_has_upper_limit = other.m_has_upper_limit;
        m_lower_limit = other.m_lower_limit;
        m_upper_limit = other.m_upper_limit;
    }
    return *this;
}


void FitParameter::print(std::ostream &ostr) const
{
    ostr << "FitParameter '" << getName() << "'" << " value:" << m_value << std::endl;
}
