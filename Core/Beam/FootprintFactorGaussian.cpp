#include "FootprintFactorGaussian.h"

#include "MathFunctions.h"
#include "MultiLayer.h"

const double sqrt2 = std::sqrt(2.0);

FootprintFactorGaussian::FootprintFactorGaussian(double width_ratio) : m_width_ratio(width_ratio)
{
    if (m_width_ratio < 0.0)
        throw std::runtime_error("Error in FootprintFactorGaussian::FootprintFactorGaussian: beam to "
                                 "sample widths ratio is negative");
}

FootprintFactorGaussian::~FootprintFactorGaussian() = default;

double FootprintFactorGaussian::calculate(double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in FootprintFactorGaussian::calculate: "
                                 "incident angle is out of range");
    if (m_width_ratio == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) / m_width_ratio / sqrt2;
    return MathFunctions::erf(arg);
}
