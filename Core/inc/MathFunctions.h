#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <cstdlib>

#include "Types.h"

#include "gsl/gsl_sf_bessel.h"
#include "gsl/gsl_sf_trig.h"

namespace MathFunctions
{
double Gaussian(double value, double average, double std_dev);

double GenerateNormalRandom(double average, double std_dev);

double StandardNormal(double value);

double GenerateStandardNormalRandom();

double GenerateUniformRandom();

double Bessel_J1(double value);

double Sinc(double value);

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
