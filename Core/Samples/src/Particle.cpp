#include "Particle.h"
#include "ParticleInfo.h"

Particle::Particle(complex_t refractive_index, IFormFactor *p_form_factor)
: m_ambient_refractive_index(complex_t(1.0, 0.0))
, m_refractive_index(refractive_index)
, mp_form_factor(p_form_factor)
{
    setName("Particle");
    if(mp_form_factor) registerChild(mp_form_factor);
}

Particle::Particle(complex_t refractive_index, const IFormFactor &form_factor)
: m_ambient_refractive_index(complex_t(1.0, 0.0))
, m_refractive_index(refractive_index)
, mp_form_factor(form_factor.clone())
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

std::vector<ParticleInfo*> Particle::createDistributedParticles(
        size_t samples_per_particle, double factor) const
{
    std::vector<ParticleInfo*> result;
    if (mp_form_factor->isDistributedFormFactor()) {
        std::vector<IFormFactor *> form_factors;
        std::vector<double> probabilities;
        mp_form_factor->createDistributedFormFactors(form_factors, probabilities, samples_per_particle);
        if (form_factors.size() > 0 && form_factors.size()==probabilities.size()) {
            for (size_t i=0; i<form_factors.size(); ++i) {
                Particle *new_particle = clone();
                new_particle->setSimpleFormFactor(form_factors[i]);
                ParticleInfo *p_info = new ParticleInfo(new_particle, 0, 0, probabilities[i]*factor);
                result.push_back(p_info);
            }
        }
    }
    return result;
}
