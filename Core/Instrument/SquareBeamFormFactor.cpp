#include "SquareBeamFormFactor.h"
#include "MultiLayer.h"

SquareBeamFormFactor::SquareBeamFormFactor(double width) : m_beam_width(width)
{
}

SquareBeamFormFactor::~SquareBeamFormFactor() = default;

double SquareBeamFormFactor::calculateFootprintFactor(const MultiLayer&, double) const
{
    return 1.0;
}
