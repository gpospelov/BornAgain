// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDWBA.cpp
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
#include "BornAgainNamespace.h"
#include "ILayerRTCoefficients.h"
#include "ISampleVisitor.h"
#include "LayerSpecularInfo.h"
#include "WavevectorInfo.h"

FormFactorDWBA::FormFactorDWBA(const IFormFactor& form_factor)
    : IFormFactorDecorator(form_factor)
    , mp_in_coeffs(0)
    , mp_out_coeffs(0)
{
    setName(BornAgain::FormFactorDWBAType);
}

void FormFactorDWBA::accept(ISampleVisitor* visitor) const { visitor->visit(this); }

FormFactorDWBA* FormFactorDWBA::clone() const
{
    FormFactorDWBA* result = new FormFactorDWBA(*mp_form_factor);
    result->setSpecularInfo(mp_in_coeffs, mp_out_coeffs);
    return result;
}

void FormFactorDWBA::setSpecularInfo(const ILayerRTCoefficients* p_in_coeffs,
                                     const ILayerRTCoefficients* p_out_coeffs)
{
    mp_in_coeffs = p_in_coeffs;
    mp_out_coeffs = p_out_coeffs;
}

complex_t FormFactorDWBA::evaluate(const WavevectorInfo& wavevectors) const
{
    calculateTerms(wavevectors);
    complex_t sum_terms = m_term_S + m_term_RS + m_term_SR + m_term_RSR;
    return sum_terms;
}

void FormFactorDWBA::calculateTerms(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    // Retrieve the two different incoming wavevectors in the layer
    cvector_t k_i_T = wavevectors.getKi();
    k_i_T.setZ(-mp_in_coeffs->getScalarKz());
    cvector_t k_i_R = k_i_T;
    k_i_R.setZ(-k_i_T.z());

    // Retrieve the two different outgoing wavevector bins in the layer
    cvector_t k_f_T = wavevectors.getKf();
    k_f_T.setZ(mp_out_coeffs->getScalarKz());
    cvector_t k_f_R = k_f_T;
    k_f_R.setZ(-k_f_T.z());

    // Construct the four different scattering contributions wavevector infos
    WavevectorInfo k_TT(k_i_T, k_f_T, wavelength);
    WavevectorInfo k_RT(k_i_R, k_f_T, wavelength);
    WavevectorInfo k_TR(k_i_T, k_f_R, wavelength);
    WavevectorInfo k_RR(k_i_R, k_f_R, wavelength);

    // Get the four R,T coefficients
    complex_t T_in = mp_in_coeffs->getScalarT();
    complex_t R_in = mp_in_coeffs->getScalarR();
    complex_t T_out = mp_out_coeffs->getScalarT();
    complex_t R_out = mp_out_coeffs->getScalarR();

    // The four different scattering contributions; S stands for scattering
    // off the particle, R for reflection off the layer interface
    m_term_S = T_in * mp_form_factor->evaluate(k_TT) * T_out;
    m_term_RS = R_in * mp_form_factor->evaluate(k_RT) * T_out;
    m_term_SR = T_in * mp_form_factor->evaluate(k_TR) * R_out;
    m_term_RSR = R_in * mp_form_factor->evaluate(k_RR) * R_out;
}
