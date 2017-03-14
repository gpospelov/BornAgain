#include "HomogeneousMaterial.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"

// this prefactor is equal to m_n*g_n*mu_N / (hbar^2), with
// m_n: neutron mass
// g_n: neutron g-factor (-3.826)
// mu_N: nuclear magneton
// hbar: reduced Planck constant
// Units are: 1/(nm^2 * T)
static const double Magnetic_Prefactor = -2.91042993836710484e-3;

// Unit 2x2 matrix
static const Eigen::Matrix2cd Unit_Matrix(Eigen::Matrix2cd::Identity());

// Imaginary unit
namespace {
    const complex_t I(0,1);
}

// Pauli matrices
static const Eigen::Matrix2cd Pauli_X((Eigen::Matrix2cd() << 0,  1,
                                                             1,  0).finished());
static const Eigen::Matrix2cd Pauli_Y((Eigen::Matrix2cd() << 0, -I,
                                                             I,  0).finished());
static const Eigen::Matrix2cd Pauli_Z((Eigen::Matrix2cd() << 1,  0,
                                                             0, -1).finished());

namespace {
// Used in experimental calculation of scattering matrix:
cvector_t OrthogonalToBaseVector(cvector_t base, const kvector_t vector)
{
    cvector_t projection = (base.dot(vector)/base.mag2())*base;
    return vector.complex() - projection;
}
}

HomogeneousMaterial::HomogeneousMaterial(
        const std::string& name, const complex_t refractive_index, const kvector_t magnetic_field)
    : INamed(name)
    , m_refractive_index(refractive_index)
    , m_magnetic_field(magnetic_field)
{}

HomogeneousMaterial::HomogeneousMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, const kvector_t magnetic_field)
    : INamed(name)
    , m_refractive_index(complex_t(1.0 - refractive_index_delta, refractive_index_beta))
    , m_magnetic_field(magnetic_field)
{}

HomogeneousMaterial*HomogeneousMaterial::clone() const
{
    return new HomogeneousMaterial(getName(), refractiveIndex(), magneticField());
}

HomogeneousMaterial*HomogeneousMaterial::cloneInverted() const
{
    std::string name = isScalarMaterial() ? getName()
                                          : getName()+"_inv";
    return new HomogeneousMaterial(name, refractiveIndex(), -magneticField());
}

complex_t HomogeneousMaterial::refractiveIndex() const
{
    return m_refractive_index;
}

void HomogeneousMaterial::setRefractiveIndex(const complex_t refractive_index)
{
    m_refractive_index = refractive_index;
}

bool HomogeneousMaterial::isScalarMaterial() const
{
    return m_magnetic_field == kvector_t {};
}

kvector_t HomogeneousMaterial::magneticField() const
{
    return m_magnetic_field;
}

void HomogeneousMaterial::setMagneticField(const kvector_t magnetic_field)
{
    m_magnetic_field = magnetic_field;
}

complex_t HomogeneousMaterial::scalarSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI/wavelength/wavelength;
    complex_t refractive_index = refractiveIndex();
    return prefactor * refractive_index * refractive_index;
}

complex_t HomogeneousMaterial::scalarFresnel(const kvector_t k, double n_ref) const
{
    complex_t refractive_index = refractiveIndex();
    return refractive_index*refractive_index - n_ref*n_ref*k.sin2Theta();
}

Eigen::Matrix2cd HomogeneousMaterial::polarizedSLD(const WavevectorInfo& wavevectors) const
{
    //    return getPolarizedSLDExperimental(wavevectors);
        Eigen::Matrix2cd result;
        double factor = Magnetic_Prefactor/4.0/M_PI;
        complex_t unit_factor = scalarSLD(wavevectors);
        result = unit_factor*Unit_Matrix
                + factor*Pauli_X*m_magnetic_field[0]
                + factor*Pauli_Y*m_magnetic_field[1]
                + factor*Pauli_Z*m_magnetic_field[2];
        return result;
}

// Implementation only for experimental testing purposes
// The magnetic field is here interpreted as the magnetization, which is seven orders
// of magnitude bigger in general!
Eigen::Matrix2cd HomogeneousMaterial::polarizedSLDExperimental(
        const WavevectorInfo& wavevectors) const
{
    const double mag_prefactor = 0.291e-9; // needs to be given more precisely?
    cvector_t mag_ortho = OrthogonalToBaseVector(wavevectors.getQ(), m_magnetic_field);
    complex_t unit_factor = scalarSLD(wavevectors);
    Eigen::Matrix2cd result;
    result = unit_factor*Unit_Matrix
            + mag_prefactor*Pauli_X*mag_ortho[0]
            + mag_prefactor*Pauli_Y*mag_ortho[1]
            + mag_prefactor*Pauli_Z*mag_ortho[2];
    return result;
}

Eigen::Matrix2cd HomogeneousMaterial::polarizedFresnel(const kvector_t k, double n_ref) const
{
    Eigen::Matrix2cd result;
    double factor = Magnetic_Prefactor/k.mag2();
    complex_t unit_factor = scalarFresnel(k, n_ref);
    result = unit_factor*Unit_Matrix
            + factor*Pauli_X*m_magnetic_field[0]
            + factor*Pauli_Y*m_magnetic_field[1]
            + factor*Pauli_Z*m_magnetic_field[2];
    return result;
}

const HomogeneousMaterial* HomogeneousMaterial::createTransformedMaterial(
        const Transform3D& transform) const
{
    kvector_t transformed_field = transform.transformed(m_magnetic_field);
    return new HomogeneousMaterial(getName(), refractiveIndex(), transformed_field);
}

void HomogeneousMaterial::print(std::ostream& ostr) const
{
    ostr << "HomMat:" << getName() << "<" << this << ">{ "
         << "R=" << m_refractive_index << ", B=" << m_magnetic_field << "}";
}

std::ostream& operator<<(std::ostream& ostr, const HomogeneousMaterial& m)
{
    m.print(ostr);
    return ostr;
}

bool operator==(const HomogeneousMaterial& left, const HomogeneousMaterial& right)
{
    if (left.getName() != right.getName()) return false;
    if (left.refractiveIndex() != right.refractiveIndex()) return false;
    if (left.magneticField() != right.magneticField()) return false;
    return true;
}

bool operator!=(const HomogeneousMaterial& left, const HomogeneousMaterial& right)
{
    return !(left==right);
}
