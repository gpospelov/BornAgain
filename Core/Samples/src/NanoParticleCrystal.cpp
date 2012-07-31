#include "NanoParticleCrystal.h"
#include "NanoParticleCrystalFormFactor.h"

NanoParticleCrystal::NanoParticleCrystal(const NanoParticle& nano_particle,
        const Lattice& lattice)
: m_lattice(lattice)
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
    return new NanoParticleCrystal(*mp_nano_particle, m_lattice);
}

IFormFactor* NanoParticleCrystal::createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        complex_t ambient_refractive_index) const
{
    return new NanoParticleCrystalFormFactor(this, meso_crystal_form_factor, ambient_refractive_index);
}
