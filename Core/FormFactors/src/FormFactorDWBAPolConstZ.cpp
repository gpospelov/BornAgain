// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBAPolConstZ.cpp
//! @brief     Implements class FormFactorDWBAPolConstZ.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBAPolConstZ.h"
#include <boost/scoped_ptr.hpp>

FormFactorDWBAPolConstZ::FormFactorDWBAPolConstZ(IFormFactor* p_formfactor,
        double depth)
: FormFactorDWBAPol(p_formfactor)
, m_depth(depth)
{
    setName("FormFactorDWBAPolConstZ");
}

FormFactorDWBAPolConstZ::~FormFactorDWBAPolConstZ()
{
}

FormFactorDWBAPolConstZ* FormFactorDWBAPolConstZ::clone() const
{
    FormFactorDWBAPolConstZ *p_result = new FormFactorDWBAPolConstZ(
            mp_form_factor->clone(), m_depth);
    p_result->setSpecularInfo(*mp_specular_info);
    p_result->setName(getName());
    return p_result;
}

Eigen::Matrix2cd FormFactorDWBAPolConstZ::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin, const Bin1D &phi_f_bin) const
{
    // get all different z-components of wavevectors
    const ILayerRTCoefficients *in_coeff =
            mp_specular_info->getInCoefficients();
    double alpha_f = alpha_f_bin.getMidPoint();
    double phi_f = phi_f_bin.getMidPoint();
    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
                getOutCoeffs(alpha_f, phi_f));

    complex_t kiz_1R = in_coeff->getKz()(0);
    complex_t kiz_1T = -in_coeff->getKz()(0);
    complex_t kiz_2R = in_coeff->getKz()(1);
    complex_t kiz_2T = -in_coeff->getKz()(1);
    complex_t kfz_1R = P_out_coeffs->getKz()(0);
    complex_t kfz_1T = -kfz_1R;
    complex_t kfz_2R = P_out_coeffs->getKz()(1);;
    complex_t kfz_2T = -kfz_2R;
    calculateTerms(k_i, k_f_bin, alpha_f_bin, phi_f_bin);

    // multiply with correct phases from depth of particle
    // eigenmode 1 -> eigenmode 1
    m_M11_S *= getDepthPhase(kiz_1T - kfz_1T);
    m_M11_RS *= getDepthPhase(kiz_1R - kfz_1T);
    m_M11_SR *= getDepthPhase(kiz_1T - kfz_1R);
    m_M11_RSR *= getDepthPhase(kiz_1R - kfz_1R);
    // eigenmode 1 -> eigenmode 2
    m_M12_S *= getDepthPhase(kiz_1T - kfz_2T);
    m_M12_RS *= getDepthPhase(kiz_1R - kfz_2T);
    m_M12_SR *= getDepthPhase(kiz_1T - kfz_2R);
    m_M12_RSR *= getDepthPhase(kiz_1R - kfz_2R);
    // eigenmode 2 -> eigenmode 1
    m_M21_S *= getDepthPhase(kiz_2T - kfz_1T);
    m_M21_RS *= getDepthPhase(kiz_2R - kfz_1T);
    m_M21_SR *= getDepthPhase(kiz_2T - kfz_1R);
    m_M21_RSR *= getDepthPhase(kiz_2R - kfz_1R);
    // eigenmode 2 -> eigenmode 2
    m_M22_S *= getDepthPhase(kiz_2T - kfz_2T);
    m_M22_RS *= getDepthPhase(kiz_2R - kfz_2T);
    m_M22_SR *= getDepthPhase(kiz_2T - kfz_2R);
    m_M22_RSR *= getDepthPhase(kiz_2R - kfz_2R);

    // sum up all 16 DWBA terms
    Eigen::Matrix2cd result =
            m_M11_S + m_M11_RS + m_M11_SR + m_M11_RSR +
            m_M12_S + m_M12_RS + m_M12_SR + m_M12_RSR +
            m_M21_S + m_M21_RS + m_M21_SR + m_M21_RSR +
            m_M22_S + m_M22_RS + m_M22_SR + m_M22_RSR;
    return result;
}
