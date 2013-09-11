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
#include "Exceptions.h"

FormFactorDWBAPol::FormFactorDWBAPol(IFormFactor* p_form_factor)
: mp_form_factor(p_form_factor)
, mp_specular_info(0)
{
    setName("FormFactorDWBAPol");
}

FormFactorDWBAPol::~FormFactorDWBAPol()
{
    delete mp_specular_info;
}

FormFactorDWBAPol* FormFactorDWBAPol::clone() const
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(mp_form_factor->clone());
    p_result->setSpecularInfo(*mp_specular_info);
    p_result->setName(getName());
    return p_result;
}

complex_t FormFactorDWBAPol::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f) const
{
    (void)k_i;
    (void)k_f_bin;
    (void)alpha_f;
    throw NotImplementedException("FormFactorDWBAPol::evaluate: "
            "should never be called for matrix interactions");
}

Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, Bin1D alpha_f, Bin1D phi_f) const
{
    calculateTerms(k_i, k_f1_bin, k_f2_bin, alpha_i, alpha_f, phi_f);
    Eigen::Matrix2cd result =
            m_M11_S + m_M11_RS + m_M11_SR + m_M11_RSR +
            m_M12_S + m_M12_RS + m_M12_SR + m_M12_RSR +
            m_M21_S + m_M21_RS + m_M21_SR + m_M21_RSR +
            m_M22_S + m_M22_RS + m_M22_SR + m_M22_RSR;
    return result;
}

void FormFactorDWBAPol::setSpecularInfo(
        const LayerSpecularInfo& layer_specular_info)
{
    delete mp_specular_info;
    mp_specular_info = layer_specular_info.clone();
}

void FormFactorDWBAPol::calculateTerms(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    const ILayerRTCoefficients *p_in_coeff =
            mp_specular_info->getInCoefficients();
    double alpha_f = alpha_f_bin.getMidPoint();
    double phi_f = phi_f_bin.getMidPoint();
    const ILayerRTCoefficients *p_out_coeff = getOutCoeffs(alpha_f, phi_f);
    // the required wavevectors inside the layer for
    // different eigenmodes and in- and outgoing wavevector;
    complex_t kix = k_i.x();
    complex_t kiy = k_i.y();
    cvector_t ki_1R(kix, kiy, p_in_coeff->getKz()(0));
    cvector_t ki_1T(kix, kiy, -p_in_coeff->getKz()(0));
    cvector_t ki_2R(kix, kiy, p_in_coeff->getKz()(1));
    cvector_t ki_2T(kix, kiy, -p_in_coeff->getKz()(1));
    const ILayerRTCoefficients *p_out_lower = getOutCoeffs(alpha_f_bin.m_lower,
            phi_f_bin.m_lower);
    const ILayerRTCoefficients *p_out_upper = getOutCoeffs(alpha_f_bin.m_upper,
            phi_f_bin.m_upper);
    Bin1DCVector kf_1R = k_f1_bin;
    kf_1R.m_q_lower.setZ(-(complex_t)p_out_lower->getKz()(0));
    kf_1R.m_q_upper.setZ(-(complex_t)p_out_upper->getKz()(0));
    Bin1DCVector kf_1T = k_f1_bin;
    kf_1T.m_q_lower.setZ((complex_t)p_out_lower->getKz()(0));
    kf_1T.m_q_upper.setZ((complex_t)p_out_upper->getKz()(0));
    Bin1DCVector kf_2R = k_f2_bin;
    kf_2R.m_q_lower.setZ(-(complex_t)p_out_lower->getKz()(1));
    kf_2R.m_q_upper.setZ(-(complex_t)p_out_upper->getKz()(1));
    Bin1DCVector kf_2T = k_f2_bin;
    kf_2T.m_q_lower.setZ((complex_t)p_out_lower->getKz()(1));
    kf_2T.m_q_upper.setZ((complex_t)p_out_upper->getKz()(1));
    // now each of the 16 matrix terms of the polarized DWBA is calculated:
    // NOTE: when the underlying reflection/transmission coefficients are
    // scalar, the eigenmodes have identical eigenvalues and spin polarization
    // is used as a basis; in this case however the matrices get mixed:
    //     real m_M11 = calculated m_M12
    //     real m_M12 = calculated m_M11
    //     real m_M21 = calculated m_M22
    //     real m_M22 = calculated m_M21
    // Since both eigenvalues are identical, this does not influence the result.
    Eigen::Matrix2cd ff_BA;

    // eigenmode 1 -> eigenmode 1: direct scattering
    ff_BA = mp_form_factor->evaluatePol(ki_1T, kf_1T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M11_S(0,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M11_S(0,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M11_S(1,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->T1min();
    m_M11_S(1,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->T1min();
    // eigenmode 1 -> eigenmode 1: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(ki_1R, kf_1T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M11_RS(0,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M11_RS(0,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M11_RS(1,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->R1min();
    m_M11_RS(1,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->R1min();
    // eigenmode 1 -> eigenmode 1: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(ki_1T, kf_1R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M11_SR(0,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M11_SR(0,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M11_SR(1,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->T1min();
    m_M11_SR(1,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->T1min();
    // eigenmode 1 -> eigenmode 1: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(ki_1R, kf_1R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M11_RSR(0,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M11_RSR(0,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M11_RSR(1,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->R1min();
    m_M11_RSR(1,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->R1min();

    // eigenmode 1 -> eigenmode 2: direct scattering
    ff_BA = mp_form_factor->evaluatePol(ki_1T, kf_2T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M12_S(0,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M12_S(0,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M12_S(1,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->T1min();
    m_M12_S(1,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->T1min();
    // eigenmode 1 -> eigenmode 2: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(ki_1R, kf_2T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M12_RS(0,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M12_RS(0,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M12_RS(1,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->R1min();
    m_M12_RS(1,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->R1min();
    // eigenmode 1 -> eigenmode 2: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(ki_1T, kf_2R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M12_SR(0,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M12_SR(0,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->T1plus();
    m_M12_SR(1,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->T1min();
    m_M12_SR(1,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->T1min();
    // eigenmode 1 -> eigenmode 2: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(ki_1R, kf_2R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M12_RSR(0,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M12_RSR(0,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->R1plus();
    m_M12_RSR(1,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->R1min();
    m_M12_RSR(1,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->R1min();

    // eigenmode 2 -> eigenmode 1: direct scattering
    ff_BA = mp_form_factor->evaluatePol(ki_2T, kf_1T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M21_S(0,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M21_S(0,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M21_S(1,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->T2min();
    m_M21_S(1,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->T2min();
    // eigenmode 2 -> eigenmode 1: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(ki_2R, kf_1T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M21_RS(0,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M21_RS(0,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M21_RS(1,0) = - p_out_coeff->T1min().transpose() * ff_BA * p_in_coeff->R2min();
    m_M21_RS(1,1) =  p_out_coeff->T1plus().transpose() * ff_BA * p_in_coeff->R2min();
    // eigenmode 2 -> eigenmode 1: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(ki_2T, kf_1R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M21_SR(0,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M21_SR(0,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M21_SR(1,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->T2min();
    m_M21_SR(1,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->T2min();
    // eigenmode 2 -> eigenmode 1: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(ki_2R, kf_1R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M21_RSR(0,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M21_RSR(0,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M21_RSR(1,0) = - p_out_coeff->R1min().transpose() * ff_BA * p_in_coeff->R2min();
    m_M21_RSR(1,1) =  p_out_coeff->R1plus().transpose() * ff_BA * p_in_coeff->R2min();

    // eigenmode 2 -> eigenmode 2: direct scattering
    ff_BA = mp_form_factor->evaluatePol(ki_2T, kf_2T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M22_S(0,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M22_S(0,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M22_S(1,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->T2min();
    m_M22_S(1,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->T2min();
    // eigenmode 2 -> eigenmode 2: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(ki_2R, kf_2T, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M22_RS(0,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M22_RS(0,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M22_RS(1,0) = - p_out_coeff->T2min().transpose() * ff_BA * p_in_coeff->R2min();
    m_M22_RS(1,1) =  p_out_coeff->T2plus().transpose() * ff_BA * p_in_coeff->R2min();
    // eigenmode 2 -> eigenmode 2: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(ki_2T, kf_2R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M22_SR(0,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M22_SR(0,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->T2plus();
    m_M22_SR(1,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->T2min();
    m_M22_SR(1,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->T2min();
    // eigenmode 2 -> eigenmode 2: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(ki_2R, kf_2R, Bin1DCVector(),
            alpha_i, alpha_f_bin, phi_f_bin);
    m_M22_RSR(0,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M22_RSR(0,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->R2plus();
    m_M22_RSR(1,0) = - p_out_coeff->R2min().transpose() * ff_BA * p_in_coeff->R2min();
    m_M22_RSR(1,1) =  p_out_coeff->R2plus().transpose() * ff_BA * p_in_coeff->R2min();
}
