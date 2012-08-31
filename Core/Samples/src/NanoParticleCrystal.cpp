#include "NanoParticleCrystal.h"
#include "NanoParticleCrystalFormFactor.h"
#include "FormFactorDecoratorDebyeWaller.h"

NanoParticleCrystal::NanoParticleCrystal(const NanoParticle& nano_particle,
        const Lattice& lattice)
: m_lattice(lattice)
, m_dw_factor(0.0)
{
    setName("NanoParticleCrystal");
    mp_nano_particle = nano_particle.clone();
    registerChild(mp_nano_particle);
}

NanoParticleCrystal::~NanoParticleCrystal()
{
    delete mp_nano_particle;
}

NanoParticleCrystal* NanoParticleCrystal::clone() const
{
    NanoParticleCrystal *p_new = new NanoParticleCrystal(*mp_nano_particle, m_lattice);
    p_new->setDWFactor(m_dw_factor);
    return p_new;
}

IFormFactor* NanoParticleCrystal::createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        complex_t ambient_refractive_index) const
{
    IFormFactor *p_npcrystal = new NanoParticleCrystalFormFactor(this, meso_crystal_form_factor, ambient_refractive_index);
    if (m_dw_factor>0.0) {
        return new FormFactorDecoratorDebyeWaller(p_npcrystal, m_dw_factor);
    }
    return p_npcrystal;
}
