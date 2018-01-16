#include "FootprintFactorSquare.h"
#include <math.h>
#include <stdexcept>

FootprintFactorSquare* FootprintFactorSquare::clone() const
{
    return new FootprintFactorSquare(*this);
}

double FootprintFactorSquare::calculate(double alpha) const
{
    if (alpha > M_PI || alpha < 0.0)
        throw std::runtime_error("Error in FootprintFactorSquare::calculate: "
                                 "incident angle is out of range");
    if (widthRatio() == 0.0)
        return 1.0;
    const double arg = std::sin(alpha) / widthRatio();
    return std::min(arg, 1.0);
}

FootprintFactorSquare::FootprintFactorSquare(const FootprintFactorSquare& other) = default;

static_assert(!std::is_copy_constructible<FootprintFactorSquare>::value,
              "FootprintFactorSquare should not be copy constructable");
static_assert(!std::is_copy_assignable<FootprintFactorSquare>::value,
              "FootprintFactorSquare should not be copy assignable");
