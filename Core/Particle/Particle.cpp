// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Particle.cpp
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
#include "BornAgainNamespace.h"
#include "FormFactorDecoratorPositionFactor.h"
#include "IMaterial.h"

Particle::Particle()
{
    initialize();
}

Particle::Particle(const IMaterial& p_material)
    : mP_material(p_material.clone())
{
    initialize();
}

Particle::Particle(const IMaterial& p_material, const IFormFactor& form_factor)
    : mP_material(p_material.clone())
    , mP_form_factor(form_factor.clone())
{
    initialize();
    registerChild(mP_form_factor.get());
}

Particle::Particle(const IMaterial& p_material, const IFormFactor& form_factor,
                   const IRotation& rotation)
    : mP_material(p_material.clone())
    , mP_form_factor(form_factor.clone())
{
    initialize();
    setRotation(rotation);
    registerChild(mP_form_factor.get());
}

Particle* Particle::clone() const
{
    Particle* p_result = new Particle();
    p_result->setAbundance(m_abundance);
    if (mP_form_factor)
        p_result->setFormFactor(*mP_form_factor);
    if (mP_material)
        p_result->setMaterial(*mP_material);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);

    return p_result;
}

Particle* Particle::cloneInvertB() const
{
    Particle* p_result = new Particle();
    p_result->setAbundance(m_abundance);
    if (mP_form_factor)
        p_result->setFormFactor(*mP_form_factor);
    if (mP_material)
        p_result->mP_material.reset(mP_material->cloneInverted());
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);

    return p_result;
}

IFormFactor* Particle::createSlicedFormFactor(ZLimits limits) const
{
    if (!mP_form_factor)
        return nullptr;
    std::unique_ptr<IRotation> P_rotation(IRotation::createIdentity());
    if (mP_rotation)
        P_rotation.reset(mP_rotation->clone());
    std::unique_ptr<IFormFactor> P_temp_ff(
                mP_form_factor->createSlicedFormFactor(limits, *P_rotation, m_position));
    FormFactorDecoratorMaterial* p_ff = new FormFactorDecoratorMaterial(*P_temp_ff);
    if (mP_material) {
        const std::unique_ptr<const IMaterial> P_transformed_material(
                    mP_material->createTransformedMaterial(P_rotation->getTransform3D()));
        p_ff->setMaterial(*P_transformed_material);
    }
    return p_ff;
}

void Particle::setMaterial(const IMaterial& material)
{
    if(mP_material.get() != &material)
        mP_material.reset(material.clone());
}

complex_t Particle::getRefractiveIndex() const
{
    return mP_material ? mP_material->refractiveIndex() : 0.0;
}

void Particle::setFormFactor(const IFormFactor& form_factor)
{
    if (&form_factor != mP_form_factor.get()) {
        mP_form_factor.reset(form_factor.clone());
        registerChild(mP_form_factor.get());
    }
}

std::vector<const INode*> Particle::getChildren() const
{
    return std::vector<const INode*>() << IParticle::getChildren() << mP_form_factor;
}

void Particle::initialize()
{
    setName(BornAgain::ParticleType);
    registerParticleProperties();
}
