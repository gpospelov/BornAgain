#include "Particle.h"

Particle::Particle(complex_t refractive_index, IFormFactor *p_form_factor)
: m_ambient_refractive_index(complex_t(1.0, 0.0))
, m_refractive_index(refractive_index)
, mp_form_factor(p_form_factor)
{
    setName("Particle");
    if(mp_form_factor) registerChild(mp_form_factor);
}

Particle::~Particle()
{
    delete mp_form_factor;
}

Particle* Particle::clone() const
{
    IFormFactor *p_form_factor = mp_form_factor->clone();
    Particle *p_new = new Particle(m_refractive_index, p_form_factor);
    p_new->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_new;
}
