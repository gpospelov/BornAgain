#include "MesoCrystal.h"

MesoCrystal::MesoCrystal(IClusteredParticles* p_particle_structure,
        IFormFactor* p_form_factor)
: Particle(complex_t(1.0, 0.0))
, mp_particle_structure(p_particle_structure)
, mp_meso_form_factor(p_form_factor)
{
    setName("MesoCrystal");
    registerChild(mp_particle_structure);
    registerChild(mp_meso_form_factor);
}

MesoCrystal::MesoCrystal(const IClusteredParticles &particle_structure,
        IFormFactor &form_factor)
: Particle(complex_t(1.0, 0.0))
, mp_particle_structure(particle_structure.clone())
, mp_meso_form_factor(form_factor.clone())
{
    setName("MesoCrystal");
    registerChild(mp_particle_structure);
    registerChild(mp_meso_form_factor);
}


MesoCrystal::~MesoCrystal()
{
    delete mp_meso_form_factor;
    delete mp_particle_structure;
}

MesoCrystal* MesoCrystal::clone() const
{
    return new MesoCrystal(mp_particle_structure->clone(), mp_meso_form_factor->clone());
}

std::vector<DiffuseParticleInfo*>* MesoCrystal::createDiffuseParticleInfo(
        const ParticleInfo& parent_info) const
{
    return mp_particle_structure->createDiffuseParticleInfo(parent_info);
}
