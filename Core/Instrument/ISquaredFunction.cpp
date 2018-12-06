// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISquaredFunction.cpp
//! @brief     Implements classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ISquaredFunction.h"
#include "Numeric.h"
#include <algorithm>
#include <cmath>

SquaredFunctionDefault* SquaredFunctionDefault::clone() const
{
    return new SquaredFunctionDefault();
}


double SquaredFunctionDefault::calculateSquaredError(
        double real_value, double simulated_value) const
{
    (void) simulated_value;
    return std::max(real_value,1.0);
}

// ************************************************************************** //

SquaredFunctionSimError* SquaredFunctionSimError::clone() const
{
    return new SquaredFunctionSimError();
}


double SquaredFunctionSimError::calculateSquaredError(double, double simulated_value) const
{
    return std::max(simulated_value,1.0);
}

// ************************************************************************** //

SquaredFunctionMeanSquaredError* SquaredFunctionMeanSquaredError::clone() const
{
    return new SquaredFunctionMeanSquaredError();
}


double SquaredFunctionMeanSquaredError::calculateSquaredError(
        double real_value, double simulated_value) const
{
    (void) simulated_value;
    double sigma1 = std::max(real_value,1.0);
    double sigma2 = std::max(simulated_value,1.0);
    return std::sqrt(sigma1*sigma1 + sigma2*sigma2);
}

// ************************************************************************** //

SquaredFunctionSystematicError* SquaredFunctionSystematicError::clone() const
{
    return new SquaredFunctionSystematicError(m_epsilon);
}


double SquaredFunctionSystematicError::calculateSquaredError(double real_value, double) const
{
    return std::max(std::abs(real_value) + (m_epsilon*real_value)*(m_epsilon*real_value),1.0);
}

// ************************************************************************** //

SquaredFunctionGaussianError*SquaredFunctionGaussianError::clone() const
{
    return new SquaredFunctionGaussianError(m_sigma);
}


double SquaredFunctionGaussianError::calculateSquaredError(double, double) const
{
    return m_sigma*m_sigma;
}
