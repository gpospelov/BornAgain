#include "HomogeneousMaterial.h"
#include "WavevectorInfo.h"


HomogeneousMaterial::HomogeneousMaterial(const std::string& name, double refractive_index_delta,
                                         double refractive_index_beta)
    : IMaterial(name)
    , m_refractive_index(complex_t(1.0 - refractive_index_delta, refractive_index_beta))
{
}

HomogeneousMaterial*HomogeneousMaterial::clone() const
{
    return new HomogeneousMaterial(getName(), getRefractiveIndex());
}

HomogeneousMaterial*HomogeneousMaterial::cloneInverted() const
{
    return clone();
}

const IMaterial*HomogeneousMaterial::createTransformedMaterial(const Transform3D&) const
{
    return new HomogeneousMaterial(getName(), getRefractiveIndex());
}
