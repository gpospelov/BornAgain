#include "DWBAFormFactorConstZ.h"

DWBAFormFactorConstZ::DWBAFormFactorConstZ(IFormFactor* p_form_factor, double depth)
: DWBAFormFactor(p_form_factor)
, m_depth(depth)
{
}

DWBAFormFactorConstZ::~DWBAFormFactorConstZ()
{
}

complex_t DWBAFormFactorConstZ::evaluate(cvector_t k_i, cvector_t k_f,
		double alpha_i, double alpha_f) const
{
	calculateTerms(k_i, k_f, alpha_i, alpha_f);
	complex_t k_iz = k_i.z();
	complex_t k_fz = k_f.z();
	m_term_S *= getDepthPhase(k_iz-k_fz);
	m_term_RS *= getDepthPhase(-k_iz-k_fz);
	m_term_SR *= getDepthPhase(k_iz+k_fz);
	m_term_RSR *= getDepthPhase(-k_iz+k_fz);
	return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

DWBAFormFactorConstZ* DWBAFormFactorConstZ::clone() const
{
    DWBAFormFactorConstZ *p_new = new DWBAFormFactorConstZ(mp_form_factor->clone(), m_depth);
//    p_new->setTransmissionFunction(mp_T->clone());
//    p_new->setReflectionFunction(mp_R->clone());
    p_new->setTransmissionFunction(*mp_T);
    p_new->setReflectionFunction(*mp_R);
    return p_new;
}

complex_t DWBAFormFactorConstZ::getDepthPhase(complex_t q_z) const
{
	complex_t exponent = -complex_t(0.0,1.0)*q_z*m_depth; // Minus sign for depth
	return std::exp(exponent);
}
