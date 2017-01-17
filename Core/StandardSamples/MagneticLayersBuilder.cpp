#include "MagneticLayersBuilder.h"
#include "RealParameter.h"
#include "Units.h"


MagneticSubstrateZeroFieldBuilder::MagneticSubstrateZeroFieldBuilder()
    : m_sphere_radius(5*Units::nanometer)
{
    init_parameters();
}

MultiLayer*MagneticSubstrateZeroFieldBuilder::buildSample() const
{
    return nullptr;
}

void MagneticSubstrateZeroFieldBuilder::init_parameters()
{
    registerParameter("sphere_radius", &m_sphere_radius).setUnit("nm").setNonnegative();
}
