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


namespace MathFunctions
{
double Gaussian(double value, double average, double std_dev);

double GenerateNormalRandom(double average, double std_dev);

double StandardNormal(double value);

double GenerateStandardNormalRandom();

double GenerateUniformRandom();

double Bessel_J1(double value);

double Sinc(double value);

enum TransformCase { ForwardFFT, BackwardFFT };
std::vector<complex_t > FastFourierTransform(const std::vector<complex_t > &data, TransformCase tcase);

std::vector<complex_t > FastFourierTransform(const std::vector<double > &data, TransformCase tcase);

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

#endif // MATHFUNCTIONS_H
