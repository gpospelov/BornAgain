/*
 * DoubleToComplexInterpolatingFunction.cpp
 *
 *  Created on: Apr 27, 2012
 *      Author: herck
 */

#include "DoubleToComplexInterpolatingFunction.h"
#include "Exceptions.h"

DoubleToComplexInterpolatingFunction::~DoubleToComplexInterpolatingFunction()
{
}

DoubleToComplexInterpolatingFunction::DoubleToComplexInterpolatingFunction(const std::map<double, complex_t> &value_map)
    : m_value_map(value_map)
{
	m_lower_limit = (*m_value_map.begin()).first;
	m_upper_limit = (*m_value_map.end()).first;
}

DoubleToComplexInterpolatingFunction* DoubleToComplexInterpolatingFunction::clone() const
{
    DoubleToComplexInterpolatingFunction *p_new = new DoubleToComplexInterpolatingFunction(m_value_map);
    return p_new;
}

complex_t DoubleToComplexInterpolatingFunction::evaluate(double value)
{
    if (value < m_lower_limit || value > m_upper_limit)
    {
        throw OutOfBoundsException("Cannot interpolate: argument value is outside of bounds.");
    }
    std::map<double, complex_t>::const_iterator lower_it = m_value_map.lower_bound(value);
    if ((*lower_it).first == value)
    {
        return (*lower_it).second;
    }
    else
    {
        --lower_it;
    }
    std::map<double, complex_t>::const_iterator upper_it = m_value_map.upper_bound(value);
    // Linear interpolation:
    complex_t result_difference = (*upper_it).second - (*lower_it).second;
    double interpolating_factor = (value - (*lower_it).first)/((*upper_it).first-(*lower_it).first);
    return (*lower_it).second + result_difference * interpolating_factor;
}
