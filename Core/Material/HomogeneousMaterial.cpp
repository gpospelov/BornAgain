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

Eigen::Matrix2cd HomogeneousMaterial::getScatteringMatrix(const WavevectorInfo& wavevectors) const
{
    Eigen::Matrix2cd mn2 = m_refractive_index * m_refractive_index * Eigen::Matrix2cd::Identity();
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI/wavelength/wavelength;
    return prefactor*mn2;
}

const IMaterial*HomogeneousMaterial::createTransformedMaterial(const Transform3D&) const
{
    return new HomogeneousMaterial(getName(), getRefractiveIndex());
}
