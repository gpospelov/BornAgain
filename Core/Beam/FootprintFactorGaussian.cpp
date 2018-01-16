#include "FootprintFactorGaussian.h"
#include "MathFunctions.h"

const double sqrt2 = std::sqrt(2.0);

double FootprintFactorGaussian::calculate(double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in FootprintFactorGaussian::calculate: "
                                 "incident angle is out of range");
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) / widthRatio() / sqrt2;
    return MathFunctions::erf(arg);
}
