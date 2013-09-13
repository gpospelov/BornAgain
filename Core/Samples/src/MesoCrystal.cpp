// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/MesoCrystal.cpp
//! @brief     Implements class MesoCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MesoCrystal.h"

MesoCrystal::MesoCrystal(IClusteredParticles* p_particle_structure,
        IFormFactor* p_form_factor)
    : mp_particle_structure(p_particle_structure)
    , mp_meso_form_factor(p_form_factor)
{
    setName("MesoCrystal");
    registerChild(mp_particle_structure);
    registerChild(mp_meso_form_factor);
}

MesoCrystal::MesoCrystal(const IClusteredParticles& particle_structure,
        IFormFactor& form_factor)
    : mp_particle_structure(particle_structure.clone())
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
    return new MesoCrystal(mp_particle_structure->clone(),
            mp_meso_form_factor->clone());
}

MesoCrystal* MesoCrystal::cloneInvertB() const
{
    return new MesoCrystal(mp_particle_structure->cloneInvertB(),
            mp_meso_form_factor->clone());
}

void MesoCrystal::setAmbientMaterial(const IMaterial* p_material)
{
    Particle::setAmbientMaterial(p_material);
    mp_particle_structure->setAmbientMaterial(p_material);
}

IFormFactor* MesoCrystal::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    return mp_particle_structure->createTotalFormFactor(
            *mp_meso_form_factor, mp_ambient_material,
            wavevector_scattering_factor);
}

void MesoCrystal::setSimpleFormFactor(IFormFactor* p_form_factor)
{
    if (p_form_factor != mp_meso_form_factor) {
        delete mp_meso_form_factor;
        mp_meso_form_factor = p_form_factor;
    }
}

std::vector<DiffuseParticleInfo*>* MesoCrystal::createDiffuseParticleInfo(
        const ParticleInfo& parent_info) const
{
    return mp_particle_structure->createDiffuseParticleInfo(parent_info);
}


