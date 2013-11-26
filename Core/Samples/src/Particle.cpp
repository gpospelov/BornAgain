// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Particle.cpp
//! @brief     Implements class Particle.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Particle.h"
#include "ParticleInfo.h"

#include "MaterialManager.h"


Particle::Particle()
: mp_material(0)
, mp_ambient_material(0)
, mp_form_factor(0)
{
    setName("Particle");
}

Particle::Particle(const IMaterial* p_material, IFormFactor *p_form_factor)
: mp_material(p_material)
, mp_ambient_material(0)
, mp_form_factor(p_form_factor)
{
    setName("Particle");
    if(mp_form_factor) registerChild(mp_form_factor);
}

Particle::Particle(const IMaterial* p_material, const IFormFactor& form_factor)
: mp_material(p_material)
, mp_ambient_material(0)
, mp_form_factor(form_factor.clone())
{
    setName("Particle");
    if(mp_form_factor) registerChild(mp_form_factor);
}

Particle::Particle(const IMaterial* p_material, const IFormFactor& form_factor,
        const Geometry::PTransform3D &transform)
: mp_material(p_material)
, mp_ambient_material(0)
, mp_form_factor(form_factor.clone())
, mP_transform(transform)
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
    IFormFactor *p_form_factor(0);
    if(mp_form_factor) p_form_factor = mp_form_factor->clone();

    Particle *p_new = new Particle(mp_material, p_form_factor);
    p_new->setAmbientMaterial(mp_ambient_material);

    p_new->setTransform(mP_transform);

    p_new->setName(getName());
    return p_new;
}

Particle* Particle::cloneInvertB() const
{
    IFormFactor *p_form_factor(0);
    if(mp_form_factor) p_form_factor = mp_form_factor->clone();

    const IMaterial *p_material = MaterialManager::getInvertedMaterial(
            mp_material->getName());
    const IMaterial *p_ambient_material(0);
    if (mp_ambient_material) {
        p_ambient_material = MaterialManager::getInvertedMaterial(
            mp_ambient_material->getName());
    }

    Particle *p_new = new Particle(p_material, p_form_factor);
    p_new->setAmbientMaterial(p_ambient_material);

    p_new->setTransform(mP_transform);

    p_new->setName(getName() + "_inv");
    return p_new;
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
    if (mP_transform.get()) {
        boost::scoped_ptr<const IMaterial> transformed_material(mp_material->
                createTransformedMaterial(mP_transform));
        p_ff->setMaterial(transformed_material.get());
    } else {
        p_ff->setMaterial(mp_material);
    }
    p_ff->setAmbientMaterial(mp_ambient_material);
    return p_ff;
}

std::vector<ParticleInfo*> Particle::createDistributedParticles(
        size_t samples_per_particle, double factor) const
{
    if(!mp_form_factor) throw NullPointerException("Particle::createDistributedParticles() -> No formfactor is defined.");

    std::vector<ParticleInfo*> result;
    if (mp_form_factor->isDistributedFormFactor()) {
        std::vector<IFormFactor *> form_factors;
        std::vector<double> probabilities;
        mp_form_factor->createDistributedFormFactors(form_factors, probabilities, samples_per_particle);
        if (form_factors.size() > 0 && form_factors.size()==probabilities.size()) {
            for (size_t i=0; i<form_factors.size(); ++i) {
                Particle *new_particle = clone();
                new_particle->setSimpleFormFactor(form_factors[i]);
                ParticleInfo *p_info =
                    new ParticleInfo(new_particle, 0., probabilities[i]*factor);
                result.push_back(p_info);
            }
        }
    }
    return result;
}

void Particle::setSimpleFormFactor(IFormFactor* p_form_factor)
{
    if (!p_form_factor) return;

    if (p_form_factor != mp_form_factor) {
        deregisterChild(mp_form_factor);
        delete mp_form_factor;
        mp_form_factor = p_form_factor;
        registerChild(mp_form_factor);
    }
}

std::vector<DiffuseParticleInfo*>* Particle::createDiffuseParticleInfo(
        const ParticleInfo& parent_info) const
{
    (void)parent_info;
    return 0;
}

bool Particle::hasDistributedFormFactor() const
{
    return ( !mp_form_factor ? false
                             : mp_form_factor->isDistributedFormFactor() );
}

IFormFactor* Particle::createTransformedFormFactor() const
{
    if(!mp_form_factor) return 0;
    IFormFactor *p_result;
    if(mP_transform.get()) {
        p_result = new FormFactorDecoratorTransformation(
                mp_form_factor->clone(), mP_transform);
    }
    else {
        p_result = mp_form_factor->clone();
    }
    return p_result;
}
