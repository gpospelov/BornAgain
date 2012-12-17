#include "FormFactorDWBAConstZ.h"

FormFactorDWBAConstZ::FormFactorDWBAConstZ(IFormFactor* p_form_factor, double depth)
: FormFactorDWBA(p_form_factor)
, m_depth(depth)
{
    setName("FormFactorDWBAConstZ");
}

FormFactorDWBAConstZ::~FormFactorDWBAConstZ()
{
}

complex_t FormFactorDWBAConstZ::evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
		double alpha_i, double alpha_f) const
{
	calculateTerms(k_i, k_f_bin, alpha_i, alpha_f);
	complex_t k_iz = k_i.z();
	complex_t k_fz = k_f_bin.getMidPoint().z();
	m_term_S *= getDepthPhase(k_iz-k_fz);
	m_term_RS *= getDepthPhase(-k_iz-k_fz);
	m_term_SR *= getDepthPhase(k_iz+k_fz);
	m_term_RSR *= getDepthPhase(-k_iz+k_fz);
	return m_term_S + m_term_RS + m_term_SR + m_term_RSR;
}

FormFactorDWBAConstZ* FormFactorDWBAConstZ::clone() const
{
    FormFactorDWBAConstZ *p_new = new FormFactorDWBAConstZ(mp_form_factor->clone(), m_depth);
    p_new->setReflectionTransmissionFunction(*mp_RT);
    return p_new;
}
