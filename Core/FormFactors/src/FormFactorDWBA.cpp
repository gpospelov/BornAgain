// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBA.cpp
//! @brief     Implements class FormFactorDWBA.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorDWBA.h"

FormFactorDWBA::FormFactorDWBA(IFormFactor *p_form_factor)
    : IFormFactorDecorator(p_form_factor)
    , mp_RT(0)
{
    setName("FormFactorDWBA");
}

FormFactorDWBA::~FormFactorDWBA()
{
    delete mp_RT;
}

complex_t FormFactorDWBA::evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    calculateTerms(k_i, k_f_bin, alpha_i, alpha_f);
    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

void FormFactorDWBA::calculateTerms(const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    cvector_t k_itilde(k_i.x(), k_i.y(), -k_i.z());
    Bin1DCVector k_f_bin_tilde =  k_f_bin;
    k_f_bin_tilde.m_q_lower.setZ( -k_f_bin_tilde.m_q_lower.z() );
    k_f_bin_tilde.m_q_upper.setZ( -k_f_bin_tilde.m_q_upper.z() );
    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
    const complexpair_t &ai_RT = getRT(alpha_i);
    const complexpair_t &af_RT = getRT(alpha_f);

    m_term_S = ai_RT.second*mp_form_factor->evaluate(k_i, k_f_bin, alpha_i, alpha_f)*af_RT.second;
    m_term_RS = ai_RT.first*mp_form_factor->evaluate(k_itilde, k_f_bin, alpha_i, alpha_f)*af_RT.second;
    m_term_SR = ai_RT.second*mp_form_factor->evaluate(k_i, k_f_bin_tilde, alpha_i, alpha_f)*af_RT.first;
    m_term_RSR = ai_RT.first*mp_form_factor->evaluate(k_itilde, k_f_bin_tilde, alpha_i, alpha_f)*af_RT.first;
}

FormFactorDWBA* FormFactorDWBA::clone() const
{
    FormFactorDWBA *p_new = new FormFactorDWBA(mp_form_factor->clone());
    p_new->setReflectionTransmissionFunction(*mp_RT);
    return p_new;
}
