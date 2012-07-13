#include "MesoCrystal.h"

MesoCrystal::MesoCrystal(IClusteredNanoParticles* p_nano_particle_structure,
        IFormFactor* p_form_factor)
: NanoParticle(complex_t(1.0, 0.0))
, mp_nano_particle_structure(p_nano_particle_structure)
, mp_meso_form_factor(p_form_factor)
{
}

MesoCrystal::~MesoCrystal()
{
    delete mp_meso_form_factor;
    delete mp_nano_particle_structure;
}

MesoCrystal* MesoCrystal::clone() const
{
    return new MesoCrystal(mp_nano_particle_structure->clone(), mp_meso_form_factor->clone());
}
