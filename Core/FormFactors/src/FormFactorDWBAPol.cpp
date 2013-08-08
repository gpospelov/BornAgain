// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBAPol.cpp
//! @brief     Defines class FormFactorDWBAPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBAPol.h"
#include "MagneticCoefficientsMap.h"
#include "Exceptions.h"

FormFactorDWBAPol::FormFactorDWBAPol(IFormFactor* p_formfactor)
: IFormFactorDecorator(p_formfactor)
, mp_magnetic_coeffs(0)
, mp_material(0)
, mp_ambient_material(0)
{
    setName("FormFactorDWBAPol");
}

FormFactorDWBAPol::~FormFactorDWBAPol()
{
    delete mp_magnetic_coeffs;
}

FormFactorDWBAPol* FormFactorDWBAPol::clone() const
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(mp_form_factor->clone());
    p_result->setRTInfo(*mp_magnetic_coeffs);
    p_result->setName(getName());
    return p_result;
}

void FormFactorDWBAPol::setRTInfo(
        const MagneticCoefficientsMap& magnetic_coeff_map)
{
    delete mp_magnetic_coeffs;
    mp_magnetic_coeffs = magnetic_coeff_map.clone();
}

Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f,
        double phi_f) const
{
    calculateTerms(k_i, k_f_bin, alpha_i, alpha_f, phi_f);
    //TODO: replace with real result!
    return Eigen::Matrix2cd::Zero();
}

void FormFactorDWBAPol::calculateTerms(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f,
        double phi_f) const
{
    SpecularMagnetic::LayerMatrixCoeff in_coeff =
            mp_magnetic_coeffs->incomingCoeff();
    SpecularMagnetic::LayerMatrixCoeff out_coeff = getOutCoeffs(alpha_f, phi_f);
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0,1) = 1.0;
    time_reverse_conj(1,0) = -1.0;
    // the interaction and time reversal taken together:
    kvector_t k_i_real(k_i.x().real(), k_i.y().real(),
            ((complex_t)in_coeff.kz(0)).real());
    Eigen::Matrix2cd V_eff = time_reverse_conj *
            (mp_material->getScatteringMatrix(k_i_real) -
                    mp_ambient_material->getScatteringMatrix(k_i_real));
    // now each of the 16 matrix terms of the polarized DWBA is calculated:
    // eigenmode 1 -> eigenmode 1: direct scattering
    m_M11_S(0,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.T1plus();
    m_M11_S(0,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.T1plus();
    m_M11_S(1,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.T1min();
    m_M11_S(1,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.T1min();
    // eigenmode 1 -> eigenmode 1: reflection and then scattering
    m_M11_RS(0,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.R1plus();
    m_M11_RS(0,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.R1plus();
    m_M11_RS(1,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.R1min();
    m_M11_RS(1,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.R1min();
    // eigenmode 1 -> eigenmode 1: scattering and then reflection
    m_M11_SR(0,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.T1plus();
    m_M11_SR(0,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.T1plus();
    m_M11_SR(1,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.T1min();
    m_M11_SR(1,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.T1min();
    // eigenmode 1 -> eigenmode 1: reflection, scattering and again reflection
    m_M11_RSR(0,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.R1plus();
    m_M11_RSR(0,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.R1plus();
    m_M11_RSR(1,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.R1min();
    m_M11_RSR(1,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.R1min();

    // eigenmode 1 -> eigenmode 2: direct scattering
    m_M12_S(0,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.T1plus();
    m_M12_S(0,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.T1plus();
    m_M12_S(1,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.T1min();
    m_M12_S(1,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.T1min();
    // eigenmode 1 -> eigenmode 2: reflection and then scattering
    m_M12_RS(0,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.R1plus();
    m_M12_RS(0,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.R1plus();
    m_M12_RS(1,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.R1min();
    m_M12_RS(1,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.R1min();
    // eigenmode 1 -> eigenmode 2: scattering and then reflection
    m_M12_SR(0,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.T1plus();
    m_M12_SR(0,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.T1plus();
    m_M12_SR(1,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.T1min();
    m_M12_SR(1,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.T1min();
    // eigenmode 1 -> eigenmode 2: reflection, scattering and again reflection
    m_M12_RSR(0,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.R1plus();
    m_M12_RSR(0,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.R1plus();
    m_M12_RSR(1,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.R1min();
    m_M12_RSR(1,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.R1min();

    // eigenmode 2 -> eigenmode 1: direct scattering
    m_M21_S(0,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.T2plus();
    m_M21_S(0,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.T2plus();
    m_M21_S(1,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.T2min();
    m_M21_S(1,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.T2min();
    // eigenmode 2 -> eigenmode 1: reflection and then scattering
    m_M21_RS(0,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.R2plus();
    m_M21_RS(0,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.R2plus();
    m_M21_RS(1,0) = - out_coeff.T1min().conjugate() * V_eff * in_coeff.R2min();
    m_M21_RS(1,1) =  out_coeff.T1plus().conjugate() * V_eff * in_coeff.R2min();
    // eigenmode 2 -> eigenmode 1: scattering and then reflection
    m_M21_SR(0,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.T2plus();
    m_M21_SR(0,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.T2plus();
    m_M21_SR(1,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.T2min();
    m_M21_SR(1,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.T2min();
    // eigenmode 2 -> eigenmode 1: reflection, scattering and again reflection
    m_M21_RSR(0,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.R2plus();
    m_M21_RSR(0,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.R2plus();
    m_M21_RSR(1,0) = - out_coeff.R1min().conjugate() * V_eff * in_coeff.R2min();
    m_M21_RSR(1,1) =  out_coeff.R1plus().conjugate() * V_eff * in_coeff.R2min();

    // eigenmode 2 -> eigenmode 2: direct scattering
    m_M22_S(0,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.T2plus();
    m_M22_S(0,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.T2plus();
    m_M22_S(1,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.T2min();
    m_M22_S(1,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.T2min();
    // eigenmode 2 -> eigenmode 2: reflection and then scattering
    m_M22_RS(0,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.R2plus();
    m_M22_RS(0,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.R2plus();
    m_M22_RS(1,0) = - out_coeff.T2min().conjugate() * V_eff * in_coeff.R2min();
    m_M22_RS(1,1) =  out_coeff.T2plus().conjugate() * V_eff * in_coeff.R2min();
    // eigenmode 2 -> eigenmode 2: scattering and then reflection
    m_M22_SR(0,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.T2plus();
    m_M22_SR(0,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.T2plus();
    m_M22_SR(1,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.T2min();
    m_M22_SR(1,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.T2min();
    // eigenmode 2 -> eigenmode 2: reflection, scattering and again reflection
    m_M22_RSR(0,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.R2plus();
    m_M22_RSR(0,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.R2plus();
    m_M22_RSR(1,0) = - out_coeff.R2min().conjugate() * V_eff * in_coeff.R2min();
    m_M22_RSR(1,1) =  out_coeff.R2plus().conjugate() * V_eff * in_coeff.R2min();
}

Eigen::Matrix2cd FormFactorDWBAPol::getScatteringPotential(
        const kvector_t& k) const
{
    if (!mp_material || !mp_ambient_material) {
        throw ClassInitializationException("FormFactorDWBAPol::"
                "getScatteringPotential: materials not yet initialized");
    }
    return mp_material->getScatteringMatrix(k) -
            mp_ambient_material->getScatteringMatrix(k);
}
