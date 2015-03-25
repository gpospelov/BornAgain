// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Particle.cpp
//! @brief     Implements class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Particle.h"
#include "ParticleInfo.h"
#include "Materials.h"
#include <boost/scoped_ptr.hpp>


Particle::Particle()
    : mp_material(0)
    , mp_ambient_material(0)
    , mp_form_factor(0)
{
    setName("Particle");
}


Particle::Particle(const IMaterial &p_material)
    : mp_material(p_material.clone())
    , mp_ambient_material(0)
    , mp_form_factor(0)
{
    setName("Particle");
}


Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor)
    : mp_material(p_material.clone())
    , mp_ambient_material(0)
    , mp_form_factor(form_factor.clone())
{
    setName("Particle");
    registerChild(mp_form_factor);
}


Particle::Particle(const IMaterial &p_material, const IFormFactor& form_factor,
        const IRotation &rotation)
    : mp_material(p_material.clone())
    , mp_ambient_material(0)
    , mp_form_factor(form_factor.clone())
{
    setName("Particle");
    mP_rotation.reset(rotation.clone());
    registerChild(mp_form_factor);
}


Particle::~Particle()
{
    delete mp_material;
    delete mp_ambient_material;
    delete mp_form_factor;
}


Particle* Particle::clone() const
{
    Particle *result = new Particle();

    if(mp_form_factor) result->setFormFactor(*mp_form_factor);
    result->setMaterial(*mp_material);
    result->setAmbientMaterial(*mp_ambient_material);
    if(mP_rotation.get()) result->mP_rotation.reset(mP_rotation->clone());
    result->setName(getName());

    return result;
}


Particle* Particle::cloneInvertB() const
{
    Particle *result = new Particle();
    if(mp_form_factor) result->setFormFactor(*mp_form_factor);

    if(mp_material) result->mp_material = Materials::createInvertedMaterial(mp_material);
    if(mp_ambient_material)
        result->mp_ambient_material = Materials::createInvertedMaterial(mp_ambient_material);

    if(mP_rotation.get()) result->mP_rotation.reset(mP_rotation->clone());

    result->setName(getName() + "_inv");
    return result;
}

IFormFactor* Particle::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    IFormFactor *p_transformed_ff = createTransformedFormFactor();
    if (!p_transformed_ff) {
        return 0;
    }
    FormFactorDecoratorMaterial *p_ff =
            new FormFactorDecoratorMaterial(
                    p_transformed_ff, wavevector_scattering_factor);
    if (mP_rotation.get()) {
        Geometry::Transform3D transform = mP_rotation->getTransform3D();
        boost::scoped_ptr<const IMaterial> transformed_material(mp_material->
                createTransformedMaterial(transform));
        p_ff->setMaterial(*transformed_material);
    } else {
        p_ff->setMaterial(*mp_material);
    }
    p_ff->setAmbientMaterial(*mp_ambient_material);
    return p_ff;
}

void Particle::setFormFactor(const IFormFactor &form_factor)
{
    if (&form_factor != mp_form_factor) {
        deregisterChild(mp_form_factor);
        delete mp_form_factor;
        mp_form_factor = form_factor.clone();
        registerChild(mp_form_factor);
    }
}

IFormFactor* Particle::createTransformedFormFactor() const
{
    if(!mp_form_factor) return 0;
    IFormFactor *p_result;
    if(mP_rotation.get()) {
        Geometry::Transform3D transform = mP_rotation->getTransform3D();
        p_result = new FormFactorDecoratorTransformation(
                    mp_form_factor->clone(), transform);
    }
    else {
        p_result = mp_form_factor->clone();
    }
    return p_result;
}

void Particle::applyTransformationToSubParticles(const IRotation& rotation)
{
    (void)rotation;
    return;
}
