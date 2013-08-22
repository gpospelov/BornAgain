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
: FormFactorPol(p_formfactor)
{
    setName("FormFactorDWBAPol");
}

FormFactorDWBAPol::~FormFactorDWBAPol()
{
}

FormFactorDWBAPol* FormFactorDWBAPol::clone() const
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(mp_form_factor->clone());
    p_result->setRTInfo(*mp_magnetic_coeffs);
    p_result->setName(getName());
    return p_result;
}

Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, double alpha_f, double phi_f) const
{
    calculateTerms(k_i, k_f1_bin, k_f2_bin, alpha_i, alpha_f, phi_f);
    Eigen::Matrix2cd result =
            m_M11_S + m_M11_RS + m_M11_SR + m_M11_RSR +
            m_M12_S + m_M12_RS + m_M12_SR + m_M12_RSR +
            m_M21_S + m_M21_RS + m_M21_SR + m_M21_RSR +
            m_M22_S + m_M22_RS + m_M22_SR + m_M22_RSR;
    return result;
}

void FormFactorDWBAPol::calculateTerms(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, double alpha_f, double phi_f) const
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
    double k_mag2 = std::abs(k_i.magxy2())/std::cos(alpha_i)/std::cos(alpha_i);
    Eigen::Matrix2cd V_eff = time_reverse_conj *
            (mp_material->getScatteringMatrix(k_mag2) -
             mp_ambient_material->getScatteringMatrix(k_mag2));
    // the required wavevectors inside the layer for
    // different eigenmodes and in- and outgoing wavevector;
    complex_t kix = k_i.x();
    complex_t kiy = k_i.y();
    cvector_t ki_1R(kix, kiy, in_coeff.kz(0));
    cvector_t ki_1T(kix, kiy, -in_coeff.kz(0));
    cvector_t ki_2R(kix, kiy, in_coeff.kz(1));
    cvector_t ki_2T(kix, kiy, -in_coeff.kz(1));
    Bin1DCVector kf_1R = k_f1_bin;
    kf_1R.m_q_lower.setZ(-kf_1R.m_q_lower.z());
    kf_1R.m_q_upper.setZ(-kf_1R.m_q_upper.z());
    Bin1DCVector kf_1T = k_f1_bin;
    Bin1DCVector kf_2R = k_f2_bin;
    Bin1DCVector kf_2T = k_f2_bin;
    kf_2T.m_q_lower.setZ(-kf_2T.m_q_lower.z());
    kf_2T.m_q_upper.setZ(-kf_2T.m_q_upper.z());
    // now each of the 16 matrix terms of the polarized DWBA is calculated:
    // eigenmode 1 -> eigenmode 1: direct scattering
    m_M11_S(0,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.T1plus();
    m_M11_S(0,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.T1plus();
    m_M11_S(1,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.T1min();
    m_M11_S(1,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.T1min();
    m_M11_S *= evaluate(ki_1T, kf_1T, alpha_i, alpha_f);
    // eigenmode 1 -> eigenmode 1: reflection and then scattering
    m_M11_RS(0,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.R1plus();
    m_M11_RS(0,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.R1plus();
    m_M11_RS(1,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.R1min();
    m_M11_RS(1,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.R1min();
    m_M11_RS *= evaluate(ki_1R, kf_1T, alpha_i, alpha_f);
    // eigenmode 1 -> eigenmode 1: scattering and then reflection
    m_M11_SR(0,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.T1plus();
    m_M11_SR(0,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.T1plus();
    m_M11_SR(1,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.T1min();
    m_M11_SR(1,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.T1min();
    m_M11_SR *= evaluate(ki_1T, kf_1R, alpha_i, alpha_f);
    // eigenmode 1 -> eigenmode 1: reflection, scattering and again reflection
    m_M11_RSR(0,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.R1plus();
    m_M11_RSR(0,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.R1plus();
    m_M11_RSR(1,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.R1min();
    m_M11_RSR(1,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.R1min();
    m_M11_RSR *= evaluate(ki_1R, kf_1R, alpha_i, alpha_f);

    // eigenmode 1 -> eigenmode 2: direct scattering
    m_M12_S(0,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.T1plus();
    m_M12_S(0,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.T1plus();
    m_M12_S(1,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.T1min();
    m_M12_S(1,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.T1min();
    m_M12_S *= evaluate(ki_1T, kf_2T, alpha_i, alpha_f);
    // eigenmode 1 -> eigenmode 2: reflection and then scattering
    m_M12_RS(0,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.R1plus();
    m_M12_RS(0,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.R1plus();
    m_M12_RS(1,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.R1min();
    m_M12_RS(1,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.R1min();
    m_M12_RS *= evaluate(ki_1R, kf_2T, alpha_i, alpha_f);
    // eigenmode 1 -> eigenmode 2: scattering and then reflection
    m_M12_SR(0,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.T1plus();
    m_M12_SR(0,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.T1plus();
    m_M12_SR(1,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.T1min();
    m_M12_SR(1,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.T1min();
    m_M12_SR *= evaluate(ki_1T, kf_2R, alpha_i, alpha_f);
    // eigenmode 1 -> eigenmode 2: reflection, scattering and again reflection
    m_M12_RSR(0,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.R1plus();
    m_M12_RSR(0,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.R1plus();
    m_M12_RSR(1,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.R1min();
    m_M12_RSR(1,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.R1min();
    m_M12_RSR *= evaluate(ki_1R, kf_2R, alpha_i, alpha_f);

    // eigenmode 2 -> eigenmode 1: direct scattering
    m_M21_S(0,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.T2plus();
    m_M21_S(0,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.T2plus();
    m_M21_S(1,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.T2min();
    m_M21_S(1,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.T2min();
    m_M21_S *= evaluate(ki_2T, kf_1T, alpha_i, alpha_f);
    // eigenmode 2 -> eigenmode 1: reflection and then scattering
    m_M21_RS(0,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.R2plus();
    m_M21_RS(0,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.R2plus();
    m_M21_RS(1,0) = - out_coeff.T1min().adjoint() * V_eff * in_coeff.R2min();
    m_M21_RS(1,1) =  out_coeff.T1plus().adjoint() * V_eff * in_coeff.R2min();
    m_M21_RS *= evaluate(ki_2R, kf_1T, alpha_i, alpha_f);
    // eigenmode 2 -> eigenmode 1: scattering and then reflection
    m_M21_SR(0,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.T2plus();
    m_M21_SR(0,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.T2plus();
    m_M21_SR(1,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.T2min();
    m_M21_SR(1,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.T2min();
    m_M21_SR *= evaluate(ki_2T, kf_1R, alpha_i, alpha_f);
    // eigenmode 2 -> eigenmode 1: reflection, scattering and again reflection
    m_M21_RSR(0,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.R2plus();
    m_M21_RSR(0,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.R2plus();
    m_M21_RSR(1,0) = - out_coeff.R1min().adjoint() * V_eff * in_coeff.R2min();
    m_M21_RSR(1,1) =  out_coeff.R1plus().adjoint() * V_eff * in_coeff.R2min();
    m_M21_RSR *= evaluate(ki_2R, kf_1R, alpha_i, alpha_f);

    // eigenmode 2 -> eigenmode 2: direct scattering
    m_M22_S(0,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.T2plus();
    m_M22_S(0,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.T2plus();
    m_M22_S(1,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.T2min();
    m_M22_S(1,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.T2min();
    m_M22_S *= evaluate(ki_2T, kf_2T, alpha_i, alpha_f);
    // eigenmode 2 -> eigenmode 2: reflection and then scattering
    m_M22_RS(0,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.R2plus();
    m_M22_RS(0,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.R2plus();
    m_M22_RS(1,0) = - out_coeff.T2min().adjoint() * V_eff * in_coeff.R2min();
    m_M22_RS(1,1) =  out_coeff.T2plus().adjoint() * V_eff * in_coeff.R2min();
    m_M22_RS *= evaluate(ki_2R, kf_2T, alpha_i, alpha_f);
    // eigenmode 2 -> eigenmode 2: scattering and then reflection
    m_M22_SR(0,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.T2plus();
    m_M22_SR(0,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.T2plus();
    m_M22_SR(1,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.T2min();
    m_M22_SR(1,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.T2min();
    m_M22_SR *= evaluate(ki_2T, kf_2R, alpha_i, alpha_f);
    // eigenmode 2 -> eigenmode 2: reflection, scattering and again reflection
    m_M22_RSR(0,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.R2plus();
    m_M22_RSR(0,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.R2plus();
    m_M22_RSR(1,0) = - out_coeff.R2min().adjoint() * V_eff * in_coeff.R2min();
    m_M22_RSR(1,1) =  out_coeff.R2plus().adjoint() * V_eff * in_coeff.R2min();
    m_M22_RSR *= evaluate(ki_2R, kf_2R, alpha_i, alpha_f);
}
