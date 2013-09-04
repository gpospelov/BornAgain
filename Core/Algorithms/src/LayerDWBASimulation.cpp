// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerDWBASimulation.cpp
//! @brief     Implements class LayerDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerDWBASimulation.h"

#include <cassert>

LayerDWBASimulation::LayerDWBASimulation()
: mp_specular_info(0)
{
}

LayerDWBASimulation::~LayerDWBASimulation()
{
    delete mp_specular_info;
}

Bin1DCVector LayerDWBASimulation::getKfBin(double wavelength,
        const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    assert(mp_specular_info);
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    k_f_bin.m_q_lower.setZ((complex_t)mp_specular_info->getOutCoefficients(
            alpha_bin.m_lower, 0.0)->getScalarKz());
    k_f_bin.m_q_upper.setZ((complex_t)mp_specular_info->getOutCoefficients(
            alpha_bin.m_upper, 0.0)->getScalarKz());
    return k_f_bin;
}

Bin1DCVector LayerDWBASimulation::getKfBin1_matrix(double wavelength,
        const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    assert(mp_specular_info);
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    complex_t kz_lower = mp_specular_info->getOutCoefficients(alpha_bin.m_lower,
            phi_bin.m_lower)->getKz()(0);
    complex_t kz_upper = mp_specular_info->getOutCoefficients(alpha_bin.m_upper,
            phi_bin.m_upper)->getKz()(0);
    k_f_bin.m_q_lower.setZ(kz_lower);
    k_f_bin.m_q_upper.setZ(kz_upper);
    return k_f_bin;
}

Bin1DCVector LayerDWBASimulation::getKfBin2_matrix(double wavelength,
        const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    assert(mp_specular_info != NULL);
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    complex_t kz_lower = mp_specular_info->getOutCoefficients(alpha_bin.m_lower,
            phi_bin.m_lower)->getKz()(1);
    complex_t kz_upper = mp_specular_info->getOutCoefficients(alpha_bin.m_upper,
            phi_bin.m_upper)->getKz()(1);
    k_f_bin.m_q_lower.setZ(kz_lower);
    k_f_bin.m_q_upper.setZ(kz_upper);
    return k_f_bin;}
