#include "NanoParticle.h"

NanoParticle::NanoParticle(complex_t refractive_index, IFormFactor *p_form_factor)
: mp_form_factor(p_form_factor),
  m_refractive_index(refractive_index)
{
}

NanoParticle::~NanoParticle()
{
    delete mp_form_factor;
}

NanoParticle* NanoParticle::clone() const
{
    IFormFactor *p_form_factor = mp_form_factor->clone();
    NanoParticle *p_new = new NanoParticle(m_refractive_index, p_form_factor);
    return p_new;
}

