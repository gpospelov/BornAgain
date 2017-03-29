// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISquaredFunction.cpp
//! @brief     Implements classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISquaredFunction.h"
#include "Numeric.h"
#include <algorithm>

SquaredFunctionDefault* SquaredFunctionDefault::clone() const
{
    return new SquaredFunctionDefault();
}

double SquaredFunctionDefault::calculateSquaredDifference(
        double real_value, double simulated_value) const
{
    if (Numeric::areAlmostEqual(real_value, simulated_value))
        return 0.;
    double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
    double normalization = calculateSquaredError(real_value);
    return diff_squared/normalization;
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

double SquaredFunctionSimError::calculateSquaredDifference(
        double real_value, double simulated_value) const
{
    if (Numeric::areAlmostEqual(real_value, simulated_value))
        return 0.0;
    double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
    double normalization = calculateSquaredError(real_value, simulated_value);
    return diff_squared/normalization;
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

double SquaredFunctionMeanSquaredError::calculateSquaredDifference(
        double real_value, double simulated_value) const
{
    if (Numeric::areAlmostEqual(real_value, simulated_value)) return 0.0;
    double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
    double normalization = calculateSquaredError(real_value, simulated_value);
    return diff_squared/normalization;
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

double SquaredFunctionSystematicError::calculateSquaredDifference(
        double real_value, double simulated_value) const
{
    double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
    double normalization = calculateSquaredError(real_value, simulated_value);
    return diff_squared/normalization;
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

double SquaredFunctionGaussianError::calculateSquaredDifference(
        double real_value, double simulated_value) const
{
    double diff_squared = (simulated_value-real_value)*(simulated_value-real_value);
    double sigma_squared = m_sigma*m_sigma;
    return diff_squared/sigma_squared;
}

double SquaredFunctionGaussianError::calculateSquaredError(double, double) const
{
    return m_sigma*m_sigma;
}
