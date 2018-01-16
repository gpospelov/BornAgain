#include "FootprintFactorGaussian.h"

#include "MathFunctions.h"
#include "MultiLayer.h"

const double sqrt2 = std::sqrt(2.0);

FootprintFactorGaussian::FootprintFactorGaussian(double width) : m_beam_width(width)
{
    if (m_beam_width < 0.0)
        throw std::runtime_error(
            "Error in GaussianBeamFormFactor::GaussianBeamFormFactor: beam width is negative");
}

FootprintFactorGaussian::~FootprintFactorGaussian() = default;

double FootprintFactorGaussian::calculate(const MultiLayer& sample, double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in FootprintFactorGaussian::calculate: "
                                 "incident angle is out of range");
    const double sample_size = sample.scale();
    if (m_beam_width == 0.0)
        return 1.0;
    if (std::isinf(sample_size))
        return 1.0;
    const double arg = sample_size * std::sin(alpha) / m_beam_width / sqrt2;
    return MathFunctions::erf(arg);
}
