#include "FormFactorDWBA.h"

FormFactorDWBA::FormFactorDWBA(IFormFactor *p_form_factor)
    : IFormFactorDecorator(p_form_factor)
//    , mp_T(0), mp_R(0)
    , mp_RT(0)
{
    setName("FormFactorDWBA");
}

FormFactorDWBA::~FormFactorDWBA()
{
//    delete mp_T;
//    delete mp_R;
    delete mp_RT;
}

complex_t FormFactorDWBA::evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const
{
    calculateTerms(k_i, k_f, alpha_i, alpha_f);
    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}


//void FormFactorDWBA::calculateTerms(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const {
//    cvector_t k_itilde(k_i.x(), k_i.y(), -k_i.z());
//    cvector_t k_ftilde(k_f.x(), k_f.y(), -k_f.z());
//    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
//    m_term_S = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_f, alpha_i, alpha_f)*getT(alpha_f);
//    m_term_RS = getR(alpha_i)*mp_form_factor->evaluate(k_itilde, k_f, alpha_i, alpha_f)*getT(alpha_f);
//    m_term_SR = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_ftilde, alpha_i, alpha_f)*getR(alpha_f);
//    m_term_RSR = getR(alpha_i)*mp_form_factor->evaluate(k_itilde, k_ftilde, alpha_i, alpha_f)*getR(alpha_f);
//}

//void FormFactorDWBA::calculateTerms(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const {
//    cvector_t k_itilde(k_i.x(), k_i.y(), -k_i.z());
//    cvector_t k_ftilde(k_f.x(), k_f.y(), -k_f.z());
//    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
//    complex_t T_alpha_i = getT(alpha_i);
//    complex_t R_alpha_i = getR(alpha_i);
//    complex_t T_alpha_f = getT(alpha_f);
//    complex_t R_alpha_f = getR(alpha_f);
//    m_term_S = T_alpha_i*mp_form_factor->evaluate(k_i, k_f, alpha_i, alpha_f)*T_alpha_f;
//    m_term_RS = R_alpha_i*mp_form_factor->evaluate(k_itilde, k_f, alpha_i, alpha_f)*T_alpha_f;
//    m_term_SR = T_alpha_i*mp_form_factor->evaluate(k_i, k_ftilde, alpha_i, alpha_f)*R_alpha_f;
//    m_term_RSR = R_alpha_i*mp_form_factor->evaluate(k_itilde, k_ftilde, alpha_i, alpha_f)*R_alpha_f;
//}

void FormFactorDWBA::calculateTerms(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const {
    cvector_t k_itilde(k_i.x(), k_i.y(), -k_i.z());
    cvector_t k_ftilde(k_f.x(), k_f.y(), -k_f.z());
    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
    const complexpair_t &ai_RT = getRT(alpha_i);
    const complexpair_t &af_RT = getRT(alpha_f);

//    complex_t T_alpha_i = getT(alpha_i);
//    complex_t R_alpha_i = getR(alpha_i);
//    complex_t T_alpha_f = getT(alpha_f);
//    complex_t R_alpha_f = getR(alpha_f);
    m_term_S = ai_RT.second*mp_form_factor->evaluate(k_i, k_f, alpha_i, alpha_f)*af_RT.second;
    m_term_RS = ai_RT.first*mp_form_factor->evaluate(k_itilde, k_f, alpha_i, alpha_f)*af_RT.second;
    m_term_SR = ai_RT.second*mp_form_factor->evaluate(k_i, k_ftilde, alpha_i, alpha_f)*af_RT.first;
    m_term_RSR = ai_RT.first*mp_form_factor->evaluate(k_itilde, k_ftilde, alpha_i, alpha_f)*af_RT.first;
}


FormFactorDWBA* FormFactorDWBA::clone() const
{
    FormFactorDWBA *p_new = new FormFactorDWBA(mp_form_factor->clone());
//    p_new->setTransmissionFunction(mp_T->clone());
//    p_new->setReflectionFunction(mp_R->clone());
//    p_new->setTransmissionFunction(*mp_T);
//    p_new->setReflectionFunction(*mp_R);
    p_new->setReflectionTransmissionFunction(*mp_RT);
    return p_new;
}

