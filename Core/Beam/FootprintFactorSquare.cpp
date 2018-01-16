#include "FootprintFactorSquare.h"

#include "MultiLayer.h"

FootprintFactorSquare::FootprintFactorSquare(double width) : m_beam_width(width)
{
    if (m_beam_width < 0.0)
        throw std::runtime_error(
            "Error in SquareBeamFormFactor::SquareBeamFormFactor: beam width is negative");
}

FootprintFactorSquare::~FootprintFactorSquare() = default;

double FootprintFactorSquare::calculate(const MultiLayer& sample, double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in FootprintFactorSquare::calculate: "
                                 "incident angle is out of range");
    if (m_beam_width == 0.0)
        return 1.0;
    const double sample_size = sample.scale();
    if (std::isinf(sample_size))
        return 1.0;
    const double arg = sample_size * std::sin(alpha) / m_beam_width;
    return std::min(arg, 1.0);
}
