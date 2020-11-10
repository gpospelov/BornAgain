// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/MathFunctions.cpp
//! @brief     Implements functions in namespace MathFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Base/Utils/MathFunctions.h"
#include "Base/Const/MathConstants.h"
#include <chrono>
#include <cstring>
#include <fftw3.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_sf_expint.h>
#include <gsl/gsl_sf_trig.h>
#include <limits>
#include <random>
#include <stdexcept> // need overlooked by g++ 5.4

// ************************************************************************** //
//  Various functions
// ************************************************************************** //

double MathFunctions::StandardNormal(double x)
{
    return std::exp(-x * x / 2.0) / std::sqrt(M_TWOPI);
}

double MathFunctions::Gaussian(double x, double average, double std_dev)
{
    return StandardNormal((x - average) / std_dev) / std_dev;
}

double MathFunctions::IntegratedGaussian(double x, double average, double std_dev)
{
    double normalized_x = (x - average) / std_dev;
    static double root2 = std::sqrt(2.0);
    return (gsl_sf_erf(normalized_x / root2) + 1.0) / 2.0;
}

double MathFunctions::cot(double x)
{
    return tan(M_PI_2 - x);
}

double MathFunctions::sinc(double x) // Sin(x)/x
{
    return gsl_sf_sinc(x / M_PI);
}

complex_t MathFunctions::sinc(const complex_t z) // Sin(x)/x
{
    // This is an exception from the rule that we must not test floating-point numbers for equality.
    // For small non-zero arguments, sin(z) returns quite accurately z or z-z^3/6.
    // There is no loss of precision in computing sin(z)/z.
    // Therefore there is no need for an expensive test like abs(z)<eps.
    if (z == complex_t(0., 0.))
        return 1.0;
    return std::sin(z) / z;
}

complex_t MathFunctions::tanhc(const complex_t z) // tanh(x)/x
{
    if (std::abs(z) < std::numeric_limits<double>::epsilon())
        return 1.0;
    return std::tanh(z) / z;
}

double MathFunctions::Laue(const double x, size_t N)
{
    static const double SQRT6DOUBLE_EPS = std::sqrt(6.0 * std::numeric_limits<double>::epsilon());
    auto nd = static_cast<double>(N);
    if (std::abs(nd * x) < SQRT6DOUBLE_EPS)
        return nd;
    double num = std::sin(nd * x);
    double den = std::sin(x);
    return num / den;
}

double MathFunctions::erf(double arg)
{
    if (arg < 0.0)
        throw std::runtime_error("Error in MathFunctions::erf: negative argument is not allowed");
    if (std::isinf(arg))
        return 1.0;
    return gsl_sf_erf(arg);
}

// ************************************************************************** //
//  Random number generators
// ************************************************************************** //

double MathFunctions::GenerateUniformRandom()
{
    int random_int = std::rand();
    return (double)random_int / RAND_MAX;
}

double MathFunctions::GenerateStandardNormalRandom() // using c++11 standard library
{
    unsigned seed =
        static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

double MathFunctions::GenerateNormalRandom(double average, double std_dev)
{
    return GenerateStandardNormalRandom() * std_dev + average;
}

double MathFunctions::GeneratePoissonRandom(double average) // using c++11 standard library
{
    unsigned seed =
        static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    if (average <= 0.0)
        return 0.0;
    if (average < 1000.0) { // Use std::poisson_distribution
        std::poisson_distribution<int> distribution(average);
        int sample = distribution(generator);
        return (double)sample;
    } else { // Use normal approximation
        std::normal_distribution<double> distribution(average, std::sqrt(average));
        double sample = distribution(generator);
        return std::max(0.0, sample);
    }
}
