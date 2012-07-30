#include "NanoParticle.h"

NanoParticle::NanoParticle(complex_t refractive_index, IFormFactor *p_form_factor)
: m_ambient_refractive_index(complex_t(1.0, 0.0))
, m_refractive_index(refractive_index)
, mp_form_factor(p_form_factor)
{
    setName("NanoParticle");
    registerChild(mp_form_factor);
}

NanoParticle::NanoParticle(complex_t refractive_index, const IFormFactor &p_form_factor)
: m_ambient_refractive_index(complex_t(1.0, 0.0))
, m_refractive_index(refractive_index)
, mp_form_factor(0)
{
    setName("NanoParticle");
    mp_form_factor = p_form_factor.clone();
    registerChild(mp_form_factor);
}


NanoParticle::~NanoParticle()
{
    delete mp_form_factor;
}

NanoParticle* NanoParticle::clone() const
{
    IFormFactor *p_form_factor = mp_form_factor->clone();
    NanoParticle *p_new = new NanoParticle(m_refractive_index, p_form_factor);
    p_new->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_new;
}
