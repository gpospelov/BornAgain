// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBA.cpp
//! @brief     Implements class FormFactorDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBA.h"

#include <cmath>

FormFactorDWBA::FormFactorDWBA(IFormFactor *p_form_factor)
    : IFormFactorDecorator(p_form_factor)
    , mp_in_coeffs(0)
    , mp_out_coeffs(0)
{
    setName("FormFactorDWBA");
}

FormFactorDWBA::~FormFactorDWBA()
{
}

FormFactorDWBA* FormFactorDWBA::clone() const
{
    FormFactorDWBA *result = new FormFactorDWBA(mp_form_factor->clone());
    result->setSpecularInfo(mp_in_coeffs, mp_out_coeffs);
    result->setName(getName());
    return result;
}

void FormFactorDWBA::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs,
                                     const ILayerRTCoefficients *p_out_coeffs)
{
    mp_in_coeffs = p_in_coeffs;
    mp_out_coeffs = p_out_coeffs;
}

complex_t FormFactorDWBA::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    calculateTerms(k_i, k_f_bin, alpha_f_bin);
    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

void FormFactorDWBA::calculateTerms(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    // Retrieve the two different incoming wavevectors in the layer
    cvector_t k_i_T = k_i;
    cvector_t k_i_R = k_i;
    k_i_R.setZ(-k_i_T.z());

    // Retrieve the two different outgoing wavevector bins in the layer
    Bin1DCVector k_f_T_bin = k_f_bin;
    k_f_T_bin.m_q_lower.setZ(mp_out_coeffs->getScalarKz());
    k_f_T_bin.m_q_upper.setZ(mp_out_coeffs->getScalarKz());
    Bin1DCVector k_f_R_bin = k_f_bin;
    k_f_R_bin.m_q_lower.setZ(-k_f_T_bin.m_q_lower.z());
    k_f_R_bin.m_q_upper.setZ(-k_f_T_bin.m_q_upper.z());

    // The four different scattering contributions; S stands for scattering
    // off the particle, R for reflection off the layer interface
    m_term_S = mp_in_coeffs->getScalarT()*mp_form_factor->evaluate(k_i_T,
            k_f_T_bin, alpha_f_bin) * mp_out_coeffs->getScalarT();
    m_term_RS = mp_in_coeffs->getScalarR()*mp_form_factor->evaluate(k_i_R,
            k_f_T_bin, alpha_f_bin) * mp_out_coeffs->getScalarT();
    m_term_SR = mp_in_coeffs->getScalarT()*mp_form_factor->evaluate(k_i_T,
            k_f_R_bin, alpha_f_bin) * mp_out_coeffs->getScalarR();
    m_term_RSR = mp_in_coeffs->getScalarR()*mp_form_factor->evaluate(k_i_R,
            k_f_R_bin, alpha_f_bin) * mp_out_coeffs->getScalarR();
}
