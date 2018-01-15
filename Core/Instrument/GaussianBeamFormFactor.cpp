#include "GaussianBeamFormFactor.h"
#include "MultiLayer.h"

GaussianBeamFormFactor::GaussianBeamFormFactor(double width) : m_beam_width(width)
{
}

GaussianBeamFormFactor::~GaussianBeamFormFactor() = default;

double GaussianBeamFormFactor::calculateFootprintFactor(const MultiLayer&, double) const
{
    return 1.0;
}
