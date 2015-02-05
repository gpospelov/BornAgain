// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/MesoCrystal.cpp
//! @brief     Implements class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
    MesoCrystal *p_result = new MesoCrystal(mp_particle_structure->clone(),
            mp_meso_form_factor->clone());
    if (mP_transform.get()) {
        p_result->mP_transform.reset(mP_transform->clone());
    }
    return p_result;
}

MesoCrystal* MesoCrystal::cloneInvertB() const
{
    MesoCrystal *p_result = new MesoCrystal(mp_particle_structure->cloneInvertB(),
            mp_meso_form_factor->clone());
    if (mP_transform.get()) {
        p_result->mP_transform.reset(mP_transform->clone());
    }
    return p_result;
}

void MesoCrystal::setAmbientMaterial(const IMaterial& material)
{
    mp_particle_structure->setAmbientMaterial(material);
}

const IMaterial *MesoCrystal::getAmbientMaterial() const
{
    if (!mp_particle_structure) return 0;
    return mp_particle_structure->getAmbientMaterial();
}

IFormFactor* MesoCrystal::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    return mp_particle_structure->createTotalFormFactor(
            *mp_meso_form_factor, *getAmbientMaterial(),
            wavevector_scattering_factor);
}

void MesoCrystal::applyTransformationToSubParticles(
        const Geometry::Transform3D& transform)
{
    mp_particle_structure->applyTransformation(transform);
}
