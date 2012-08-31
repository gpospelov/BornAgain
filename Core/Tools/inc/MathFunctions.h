#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MathFunctions.h
//! @brief  Collection of mathematical functions
//! @author Scientific Computing Group at FRM II
//! @date   20.04.2012

#include <cstdlib>
#include <vector>
#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_sf_trig.h"
#include "Types.h"
#include "Numeric.h"


namespace MathFunctions
{
double Gaussian(double value, double average, double std_dev);

double IntegratedGaussian(double value, double average, double std_dev);

double GenerateNormalRandom(double average, double std_dev);

double StandardNormal(double value);

double GenerateStandardNormalRandom();

double GenerateUniformRandom();

double Bessel_J1(double value);

complex_t Bessel_J1(complex_t value);

double Sinc(double value);

complex_t Sinc(complex_t value);

complex_t Laue(complex_t value, size_t N);

enum TransformCase { ForwardFFT, BackwardFFT };
std::vector<complex_t > FastFourierTransform(const std::vector<complex_t > &data, TransformCase tcase);

std::vector<complex_t > FastFourierTransform(const std::vector<double > &data, TransformCase tcase);

std::vector<complex_t> ConvolveFFT(const std::vector<double> &signal, const std::vector<double> &resfunc);

} // Namespace MathFunctions

inline double MathFunctions::GenerateNormalRandom(double average, double std_dev)
{
    return GenerateStandardNormalRandom()*std_dev + average;
}

inline double MathFunctions::GenerateUniformRandom()
{
    int random_int = std::rand();
    return (double)random_int / RAND_MAX;
}

inline double MathFunctions::Bessel_J1(double value)
{
    return gsl_sf_bessel_J1(value);
}

inline double MathFunctions::Sinc(double value)  // Sin(x)/x
{
    return gsl_sf_sinc(value/M_PI);
}

inline complex_t MathFunctions::Sinc(complex_t value)  // Sin(x)/x
{
	if(std::abs(value)<Numeric::double_epsilon) {
		return complex_t(1.0, 0.0);
	}
    return (std::exp(complex_t(0.0, 1.0)*value) - std::exp(complex_t(0.0, -1.0)*value))
    		/(complex_t(0.0, 2.0)*value);
}

inline complex_t MathFunctions::Laue(complex_t value, size_t N) // Exp(iNx/2)*Sin((N+1)x)/Sin(x)
{
    if (N==0) {
        return complex_t(1.0, 0.0);
    }
    if(std::abs(value)<Numeric::double_epsilon) {
        return complex_t(N+1.0, 0.0);
    }
    return std::exp(complex_t(0.0, 1.0)*value*(double)N/2.0)*std::sin(value*(N+1.0)/2.0)/std::sin(value/2.0);
}

#endif // MATHFUNCTIONS_H
