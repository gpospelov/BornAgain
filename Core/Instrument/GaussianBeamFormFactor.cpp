#include "GaussianBeamFormFactor.h"
#include "MathFunctions.h"
#include "MultiLayer.h"

const double sqrt2 = std::sqrt(2.0);

GaussianBeamFormFactor::GaussianBeamFormFactor(double width) : m_beam_width(width)
{
    if (m_beam_width < 0.0)
        throw std::runtime_error(
            "Error in GaussianBeamFormFactor::GaussianBeamFormFactor: beam width is negative");
}

GaussianBeamFormFactor::~GaussianBeamFormFactor() = default;

double GaussianBeamFormFactor::calculateFootprintFactor(const MultiLayer& sample, double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in GaussianBeamFormFactor::calculateFootprintFactor: "
                                 "incident angle is out of range");
    const double sample_size = sample.scale();
    if (m_beam_width == 0.0)
        return 1.0;
    if (std::isinf(sample_size))
        return 1.0;
    const double arg = sample_size * std::sin(alpha) / m_beam_width / sqrt2;
    return MathFunctions::erf(arg);
}
