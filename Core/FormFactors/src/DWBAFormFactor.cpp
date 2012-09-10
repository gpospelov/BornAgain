#include "DWBAFormFactor.h"

DWBAFormFactor::DWBAFormFactor(IFormFactor *p_form_factor)
    : IFormFactorDecorator(p_form_factor)
    , mp_T(0), mp_R(0)
{
}

DWBAFormFactor::~DWBAFormFactor()
{
    delete mp_form_factor;
    delete mp_T;
    delete mp_R;
}

complex_t DWBAFormFactor::evaluate(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const
{
    calculateTerms(k_i, k_f, alpha_i, alpha_f);
    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}


void DWBAFormFactor::calculateTerms(cvector_t k_i, cvector_t k_f, double alpha_i, double alpha_f) const {
    cvector_t k_itilde(k_i.x(), k_i.y(), -k_i.z());
    cvector_t k_ftilde(k_f.x(), k_f.y(), -k_f.z());
    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
    m_term_S = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_f, alpha_i, alpha_f)*getT(alpha_f);
    m_term_RS = getR(alpha_i)*mp_form_factor->evaluate(k_itilde, k_f, alpha_i, alpha_f)*getT(alpha_f);
    m_term_SR = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_ftilde, alpha_i, alpha_f)*getR(alpha_f);
    m_term_RSR = getR(alpha_i)*mp_form_factor->evaluate(k_itilde, k_ftilde, alpha_i, alpha_f)*getR(alpha_f);
}

DWBAFormFactor* DWBAFormFactor::clone() const
{
    DWBAFormFactor *p_new = new DWBAFormFactor(mp_form_factor->clone());
//    p_new->setTransmissionFunction(mp_T->clone());
//    p_new->setReflectionFunction(mp_R->clone());
    p_new->setTransmissionFunction(*mp_T);
    p_new->setReflectionFunction(*mp_R);
    return p_new;
}
