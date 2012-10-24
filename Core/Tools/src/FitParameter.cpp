#include "FitParameter.h"
#include <iostream>


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


//FitParameter::FitParameter(const FitParameter &other) : INamed(other), AttLimits(other)
//{
//    m_value = other.m_value;
//    m_step = other.m_step;
//    m_error = other.m_error;
//    m_has_lower_limit = other.m_has_lower_limit;
//    m_has_upper_limit = other.m_has_upper_limit;
//    m_lower_limit = other.m_lower_limit;
//    m_upper_limit = other.m_upper_limit;
//}


//FitParameter &FitParameter::operator=(const FitParameter &other)
//{
//    if( this != &other)
//    {
//        INamed::operator=(other);
//        m_value = other.m_value;
//        m_step = other.m_step;
//        m_error = other.m_error;
//        m_has_lower_limit = other.m_has_lower_limit;
//        m_has_upper_limit = other.m_has_upper_limit;
//        m_lower_limit = other.m_lower_limit;
//        m_upper_limit = other.m_upper_limit;
//    }
//    return *this;
//}


void FitParameter::print(std::ostream &ostr) const
{
    ostr << "FitParameter '" << getName() << "'" << " value:" << m_value << std::endl;
}
