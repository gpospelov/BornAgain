#include "HomogeneousMaterial.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"
#include "MaterialUtils.h"
#include "PhysicalConstants.h"

using PhysConsts::mu_B;
using PhysConsts::gamma_n;
using PhysConsts::r_e;
 // The factor 1e-18 is here to have unit: m/A*nm^-2
constexpr double magnetization_prefactor
    = (gamma_n * r_e / 2.0 / mu_B) * 1e-18;

namespace {
// Used in experimental calculation of scattering matrix:
cvector_t OrthogonalToBaseVector(cvector_t base, const kvector_t vector)
{
    if (base.mag2()==0.0) return cvector_t {};
    cvector_t projection = (base.dot(vector)/base.mag2())*base;
    return vector.complex() - projection;
}
}

HomogeneousMaterial::HomogeneousMaterial()
    : INamed("vacuum")
    , m_refractive_index(1)
{}

HomogeneousMaterial::HomogeneousMaterial(
        const std::string& name, const complex_t refractive_index, kvector_t magnetization)
    : INamed(name)
    , m_refractive_index(refractive_index)
    , m_magnetization(magnetization)
{}

HomogeneousMaterial::HomogeneousMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, kvector_t magnetization)
    : INamed(name)
    , m_refractive_index(complex_t(1.0 - refractive_index_delta, refractive_index_beta))
    , m_magnetization(magnetization)
{}

HomogeneousMaterial HomogeneousMaterial::inverted() const
{
    std::string name = isScalarMaterial() ? getName()
                                          : getName()+"_inv";
    complex_t material_data = materialData();
    HomogeneousMaterial result(name, material_data.real(), material_data.imag(), -magnetization());
    return result;
}

complex_t HomogeneousMaterial::refractiveIndex(double) const
{
    return m_refractive_index;
}

complex_t HomogeneousMaterial::refractiveIndex2(double) const
{
    return m_refractive_index*m_refractive_index;
}

bool HomogeneousMaterial::isScalarMaterial() const
{
    return m_magnetization == kvector_t {};
}

kvector_t HomogeneousMaterial::magnetization() const
{
    return m_magnetization;
}

complex_t HomogeneousMaterial::materialData() const
{
    return complex_t(1.0 - m_refractive_index.real(), m_refractive_index.imag());
}

complex_t HomogeneousMaterial::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI/wavelength/wavelength;
    return prefactor * refractiveIndex2(wavelength);
}

Eigen::Matrix2cd HomogeneousMaterial::polarizedSubtrSLD(const WavevectorInfo& wavevectors) const
{
    cvector_t mag_ortho = OrthogonalToBaseVector(wavevectors.getQ(), m_magnetization);
    complex_t unit_factor = scalarSubtrSLD(wavevectors);
    return MagnetizationCorrection(unit_factor, magnetization_prefactor, mag_ortho);
}

HomogeneousMaterial HomogeneousMaterial::transformedMaterial(const Transform3D& transform) const
{
    kvector_t transformed_field = transform.transformed(m_magnetization);
    complex_t material_data = materialData();
    return HomogeneousMaterial(getName(), material_data.real(), material_data.imag(), transformed_field);
}

void HomogeneousMaterial::print(std::ostream& ostr) const
{
    ostr << "HomMat:" << getName() << "<" << this << ">{ "
         << "R=" << m_refractive_index << ", B=" << m_magnetization << "}";
}

std::ostream& operator<<(std::ostream& ostr, const HomogeneousMaterial& m)
{
    m.print(ostr);
    return ostr;
}

bool operator==(const HomogeneousMaterial& left, const HomogeneousMaterial& right)
{
    if (left.getName() != right.getName()) return false;
    if (left.magnetization() != right.magnetization()) return false;
    if (left.materialData() != right.materialData()) return false;
    return true;
}

bool operator!=(const HomogeneousMaterial& left, const HomogeneousMaterial& right)
{
    return !(left==right);
}
