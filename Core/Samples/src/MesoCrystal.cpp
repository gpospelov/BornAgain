// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Samples/MesoCrystal.cpp 
//! @brief     Implements class MesoCrystal.
//
// ************************************************************************** //

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
