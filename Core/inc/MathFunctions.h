#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <cstdlib>

namespace MathFunctions
{
double Gaussian(double value, double average, double std_dev);

double GenerateNormalRandom(double average, double std_dev);

double StandardNormal(double value);

double GenerateStandardNormalRandom();

double GenerateUniformRandom();

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

#endif // MATHFUNCTIONS_H
