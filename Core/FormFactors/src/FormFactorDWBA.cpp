// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBA.cpp
//! @brief     Implements class FormFactorDWBA.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBA.h"

FormFactorDWBA::FormFactorDWBA(IFormFactor *p_form_factor)
    : IFormFactorDecorator(p_form_factor)
    , mp_specular_info(0)
{
    setName("FormFactorDWBA");
}

FormFactorDWBA::~FormFactorDWBA()
{
    delete mp_specular_info;
}

FormFactorDWBA* FormFactorDWBA::clone() const
{
    FormFactorDWBA *result = new FormFactorDWBA(mp_form_factor->clone());
    if (mp_specular_info) {
        result->setSpecularInfo(*mp_specular_info);
    }
    result->setName(getName());
    return result;
}

complex_t FormFactorDWBA::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    calculateTerms(k_i, k_f_bin, alpha_i, alpha_f);
    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

void FormFactorDWBA::setSpecularInfo(
        const LayerSpecularInfo& layer_specular_info)
{
    delete mp_specular_info;
    mp_specular_info = layer_specular_info.clone();
}

void FormFactorDWBA::calculateTerms(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    cvector_t k_itilde(k_i.x(), k_i.y(), -k_i.z());
    Bin1DCVector k_f_bin_tilde =  k_f_bin;
    k_f_bin_tilde.m_q_lower.setZ( -k_f_bin_tilde.m_q_lower.z() );
    k_f_bin_tilde.m_q_upper.setZ( -k_f_bin_tilde.m_q_upper.z() );
    // The four different scattering contributions; S stands for scattering
    // off the particle, R for reflection off the layer interface
    const ILayerRTCoefficients *p_in_coeff =
            mp_specular_info->getInCoefficients();
    const ILayerRTCoefficients *p_out_coeff = getOutCoeffs(alpha_f);

    m_term_S = p_in_coeff->getScalarT()*mp_form_factor->evaluate(k_i, k_f_bin,
            alpha_i, alpha_f)*p_out_coeff->getScalarT();
    m_term_RS = p_in_coeff->getScalarR()*mp_form_factor->evaluate(k_itilde,
            k_f_bin, alpha_i, alpha_f)*p_out_coeff->getScalarT();
    m_term_SR = p_in_coeff->getScalarT()*mp_form_factor->evaluate(k_i,
            k_f_bin_tilde, alpha_i, alpha_f)*p_out_coeff->getScalarR();
    m_term_RSR = p_in_coeff->getScalarR()*mp_form_factor->evaluate(k_itilde,
            k_f_bin_tilde, alpha_i, alpha_f)*p_out_coeff->getScalarR();
}


