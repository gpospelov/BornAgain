#include "HomogeneousMaterial.h"
#include "WavevectorInfo.h"


HomogeneousMaterial::HomogeneousMaterial(const std::string& name, const complex_t refractive_index)
    : IMaterial(name)
    , m_refractive_index(refractive_index)
{}

HomogeneousMaterial::HomogeneousMaterial(const std::string& name, double refractive_index_delta,
                                         double refractive_index_beta)
    : IMaterial(name)
    , m_refractive_index(complex_t(1.0 - refractive_index_delta, refractive_index_beta))
{}

HomogeneousMaterial*HomogeneousMaterial::clone() const
{
    return new HomogeneousMaterial(getName(), refractiveIndex());
}

HomogeneousMaterial*HomogeneousMaterial::cloneInverted() const
{
    return clone();
}

complex_t HomogeneousMaterial::refractiveIndex() const
{
    return m_refractive_index;
}

void HomogeneousMaterial::setRefractiveIndex(const complex_t refractive_index)
{
    m_refractive_index = refractive_index;
}

const IMaterial*HomogeneousMaterial::createTransformedMaterial(const Transform3D&) const
{
    return new HomogeneousMaterial(getName(), refractiveIndex());
}

void HomogeneousMaterial::print(std::ostream& ostr) const
{
    ostr << "HomMat:" << getName() << "<" << this << ">{ "
         << "R=" << m_refractive_index << "}";
}
