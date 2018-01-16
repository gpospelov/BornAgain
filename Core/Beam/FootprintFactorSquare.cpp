#include "FootprintFactorSquare.h"

#include "MultiLayer.h"

FootprintFactorSquare::FootprintFactorSquare(double width_ratio) : m_width_ratio(width_ratio)
{
    if (m_width_ratio < 0.0)
        throw std::runtime_error(
            "Error in FootprintFactorSquare::FootprintFactorSquare: beam width is negative");
}

FootprintFactorSquare::~FootprintFactorSquare() = default;

double FootprintFactorSquare::calculate(double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in FootprintFactorSquare::calculate: "
                                 "incident angle is out of range");
    if (m_width_ratio == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) / m_width_ratio;
    return std::min(arg, 1.0);
}
