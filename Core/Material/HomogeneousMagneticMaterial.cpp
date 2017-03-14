// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/HomogeneousMagneticMaterial.cpp
//! @brief     Implements class HomogeneousMagneticMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "HomogeneousMagneticMaterial.h"
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

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, const complex_t refractive_index,
        const kvector_t magnetic_field)
: HomogeneousMaterial(name, refractive_index)
, m_magnetic_field(magnetic_field)
{}

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, const kvector_t magnetic_field)
    : HomogeneousMaterial(name, refractive_index_delta, refractive_index_beta)
    , m_magnetic_field(magnetic_field)
{}

HomogeneousMagneticMaterial* HomogeneousMagneticMaterial::clone() const
{
    return new HomogeneousMagneticMaterial(getName(), refractiveIndex(), magneticField());
}

HomogeneousMagneticMaterial* HomogeneousMagneticMaterial::cloneInverted() const
{
    return new HomogeneousMagneticMaterial(
        getName()+"_inv", refractiveIndex(), -magneticField());
}

kvector_t HomogeneousMagneticMaterial::magneticField() const
{
    return m_magnetic_field;
}

Eigen::Matrix2cd HomogeneousMagneticMaterial::polarizedSLD(
        const WavevectorInfo& wavevectors) const
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
Eigen::Matrix2cd HomogeneousMagneticMaterial::polarizedSLDExperimental(
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

Eigen::Matrix2cd HomogeneousMagneticMaterial::polarizedFresnel(
        const kvector_t k, double n_ref) const
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

const IMaterial* HomogeneousMagneticMaterial::createTransformedMaterial(
        const Transform3D& transform) const
{
    kvector_t mag_field_transformed = transform.transformed(m_magnetic_field);
    return new HomogeneousMagneticMaterial(getName(), refractiveIndex(),
            mag_field_transformed);
}

void HomogeneousMagneticMaterial::print(std::ostream& ostr) const
{
    ostr << "HomMagMat:" << getName() << "<" << this << ">{ "
         << "R=" << m_refractive_index << ", B=" << m_magnetic_field << "}";
}
