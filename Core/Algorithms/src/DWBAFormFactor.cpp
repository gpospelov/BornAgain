#include "DWBAFormFactor.h"

DWBAFormFactor::DWBAFormFactor(IFormFactor *p_form_factor)
    : mp_form_factor(p_form_factor)
    , mp_T(0), mp_R(0)
{
}

DWBAFormFactor::~DWBAFormFactor()
{
    delete mp_form_factor;
    delete mp_T;
    delete mp_R;
}

complex_t DWBAFormFactor::evaluate(kvector_t k_i, kvector_t k_f) const
{
    return evaluateForComplexkz(k_i, k_f, k_i.z(), k_f.z());
}

complex_t DWBAFormFactor::evaluateForComplexkz(kvector_t k_i, kvector_t k_f,
		complex_t k_iz, complex_t k_fz) const
{
	calculateTerms(k_i, k_f, k_iz, k_fz);
    return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

void DWBAFormFactor::calculateTerms(kvector_t k_i, kvector_t k_f) const {
    kvector_t k_i_mirror_xy(k_i.x(), k_i.y(), -k_i.z());
    kvector_t k_f_mirror_xy(k_f.x(), k_f.y(), -k_f.z());
    double alpha_i = -std::asin(k_i.z()/k_i.mag());
    double alpha_f = std::asin(k_f.z()/k_f.mag());
    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
    m_term_S = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_f)*getT(alpha_f);
    m_term_RS = getR(alpha_i)*mp_form_factor->evaluate(k_i_mirror_xy, k_f)*getT(alpha_f);
    m_term_SR = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_f_mirror_xy)*getR(alpha_f);
    m_term_RSR = getR(alpha_i)*mp_form_factor->evaluate(k_i_mirror_xy, k_f_mirror_xy)*getR(alpha_f);
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

void DWBAFormFactor::calculateTerms(kvector_t k_i, kvector_t k_f,
    		complex_t k_iz, complex_t k_fz) const
{
    double alpha_i = -std::asin(k_i.z()/k_i.mag());
    double alpha_f = std::asin(k_f.z()/k_f.mag());
    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
    m_term_S = getT(alpha_i)*mp_form_factor->evaluateForComplexkz(k_i, k_f, k_iz, k_fz)*getT(alpha_f);
    m_term_RS = getR(alpha_i)*mp_form_factor->evaluateForComplexkz(k_i, k_f, -k_iz, k_fz)*getT(alpha_f);
    m_term_SR = getT(alpha_i)*mp_form_factor->evaluateForComplexkz(k_i, k_f, k_iz, -k_fz)*getR(alpha_f);
    m_term_RSR = getR(alpha_i)*mp_form_factor->evaluateForComplexkz(k_i, k_f, -k_iz, -k_fz)*getR(alpha_f);
}
