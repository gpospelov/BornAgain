#include "MathFunctions.h"

#include <cmath>

double MathFunctions::Gaussian(double value, double average, double std_dev)
{
    return StandardNormal((value-average)/std_dev)/std_dev;
}

double MathFunctions::StandardNormal(double value)
{
    return std::exp(- value*value / 2.0) / std::sqrt(2.0*M_PI);
}

double MathFunctions::GenerateStandardNormalRandom()  // using Box-Muller transform
{
    double u1 = GenerateUniformRandom();
    double u2 = GenerateUniformRandom();
    return std::sqrt(-2.0*std::log(u1))*std::cos(2*M_PI*u2);
}
