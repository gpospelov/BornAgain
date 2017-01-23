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
const double HomogeneousMagneticMaterial::m_magnetic_prefactor = -2.91042993836710484e-3;

namespace {
// Used in experimental calculation of scattering matrix:
cvector_t OrthogonalToBaseVector(const cvector_t base, const kvector_t vector)
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
{
    initializePrivateMembers();
}

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, const kvector_t magnetic_field)
    : HomogeneousMaterial(name, refractive_index_delta, refractive_index_beta)
    , m_magnetic_field(magnetic_field)
{
    initializePrivateMembers();
}

HomogeneousMagneticMaterial* HomogeneousMagneticMaterial::clone() const
{
    return new HomogeneousMagneticMaterial(getName(), getRefractiveIndex(), getMagneticField());
}

HomogeneousMagneticMaterial* HomogeneousMagneticMaterial::cloneInverted() const
{
    return new HomogeneousMagneticMaterial(
        getName()+"_inv", getRefractiveIndex(), -getMagneticField());
}

Eigen::Matrix2cd HomogeneousMagneticMaterial::getPolarizedSLD(
        const WavevectorInfo& wavevectors) const
{
//    return getPolarizedSLDExperimental(wavevectors);
    Eigen::Matrix2cd result;
    double factor = m_magnetic_prefactor/4.0/M_PI;
    complex_t unit_factor = getScalarSLD(wavevectors);
    result = unit_factor*m_unit_matrix
            + factor*m_pauli_operator[0]*m_magnetic_field[0]
            + factor*m_pauli_operator[1]*m_magnetic_field[1]
            + factor*m_pauli_operator[2]*m_magnetic_field[2];
    return result;
}

// Implementation only for experimental testing purposes
// The magnetic field is here interpreted as the magnetization, which is seven orders
// of magnitude bigger in general!
Eigen::Matrix2cd HomogeneousMagneticMaterial::getPolarizedSLDExperimental(
        const WavevectorInfo& wavevectors) const
{
    const double mag_prefactor = 0.291e-9; // needs to be given more precisely?
    cvector_t mag_ortho = OrthogonalToBaseVector(wavevectors.getQ(), m_magnetic_field);
    complex_t unit_factor = getScalarSLD(wavevectors);
    Eigen::Matrix2cd result;
    result = unit_factor*m_unit_matrix
            + mag_prefactor*m_pauli_operator[0]*mag_ortho[0]
            + mag_prefactor*m_pauli_operator[1]*mag_ortho[1]
            + mag_prefactor*m_pauli_operator[2]*mag_ortho[2];
    return result;
}

Eigen::Matrix2cd HomogeneousMagneticMaterial::getPolarizedFresnel(const kvector_t k) const
{
    Eigen::Matrix2cd result;
    double factor = m_magnetic_prefactor/k.mag2();
    complex_t unit_factor = getScalarFresnel(k);
    result = unit_factor*m_unit_matrix
            + factor*m_pauli_operator[0]*m_magnetic_field[0]
            + factor*m_pauli_operator[1]*m_magnetic_field[1]
            + factor*m_pauli_operator[2]*m_magnetic_field[2];
    return result;
}

const IMaterial* HomogeneousMagneticMaterial::createTransformedMaterial(
        const Transform3D& transform) const
{
    kvector_t mag_field_transformed = transform.transformed(m_magnetic_field);
    return new HomogeneousMagneticMaterial(getName(), getRefractiveIndex(),
            mag_field_transformed);
}

void HomogeneousMagneticMaterial::initializePrivateMembers()
{
    m_unit_matrix.setIdentity();
    m_pauli_operator.clear();
    Eigen::Matrix2cd sigma;
    sigma(0,0) = 0.0;
    sigma(0,1) = 1.0;
    sigma(1,0) = 1.0;
    sigma(1,1) = 0.0;
    m_pauli_operator.push_back(sigma);
    sigma(0,0) = 0.0;
    sigma(0,1) = complex_t(0.0, -1.0);
    sigma(1,0) = complex_t(0.0, 1.0);
    sigma(1,1) = 0.0;
    m_pauli_operator.push_back(sigma);
    sigma(0,0) = 1.0;
    sigma(0,1) = 0.0;
    sigma(1,0) = 0.0;
    sigma(1,1) = -1.0;
    m_pauli_operator.push_back(sigma);
}
