// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      HomogeneousMagneticMaterial.cpp
//! @brief     Implements class HomogeneousMagneticMaterial.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "HomogeneousMagneticMaterial.h"

const double HomogeneousMagneticMaterial::m_magnetic_prefactor
                 = -2.91042993836710484e-3;

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, const complex_t& refractive_index,
        const kvector_t& magnetic_field)
: HomogeneousMaterial(name, refractive_index)
, m_magnetic_field(magnetic_field)
{
    initializePrivateMemebers();
}

HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, const kvector_t& magnetic_field)
: HomogeneousMaterial(name, refractive_index_delta, refractive_index_beta)
, m_magnetic_field(magnetic_field)
{
    initializePrivateMemebers();
}

Eigen::Matrix2cd HomogeneousMagneticMaterial::getScatteringMatrix(
        const kvector_t& k) const
{
    Eigen::Matrix2cd result;
    double kmag = k.mag();
    double factor = m_magnetic_prefactor/kmag/kmag;
    result = m_refractive_index*m_refractive_index*m_unit_matrix
            + factor*m_pauli_operator[0]*m_magnetic_field[0]
            + factor*m_pauli_operator[1]*m_magnetic_field[1]
            + factor*m_pauli_operator[2]*m_magnetic_field[2];
    return result;
}

void HomogeneousMagneticMaterial::initializePrivateMemebers()
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
