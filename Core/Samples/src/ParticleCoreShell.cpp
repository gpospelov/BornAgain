// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleCoreShell.cpp
//! @brief     Implements class ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCoreShell.h"
#include "FormFactors.h"
#include "Materials.h"
#include <boost/scoped_ptr.hpp>


ParticleCoreShell::ParticleCoreShell(const Particle& shell,
        const Particle& core, kvector_t relative_core_position)
    : mp_shell(0)
    , mp_core(0)
    , m_relative_core_position(relative_core_position)
{
    setName("ParticleCoreShell");
    addAndRegisterCore(core);
    addAndRegisterShell(shell);
}

ParticleCoreShell::~ParticleCoreShell()
{
    delete mp_shell;
    delete mp_core;
}

ParticleCoreShell *ParticleCoreShell::clone() const
{
    ParticleCoreShell *p_new = new ParticleCoreShell(*mp_shell, *mp_core,
            m_relative_core_position);
    p_new->setAmbientMaterial(*getAmbientMaterial());
    if (mP_rotation.get()) {
        p_new->mP_rotation.reset(mP_rotation->clone());
    }
    p_new->setName(getName());
    return p_new;
}

ParticleCoreShell* ParticleCoreShell::cloneInvertB() const
{
    ParticleCoreShell *p_new = new ParticleCoreShell(m_relative_core_position);
    p_new->mp_shell = this->mp_shell->cloneInvertB();
    p_new->mp_core = this->mp_core->cloneInvertB();
    p_new->setAmbientMaterial( *Materials::createInvertedMaterial(getAmbientMaterial()) );
    if (mP_rotation.get()) {
        p_new->mP_rotation.reset(mP_rotation->clone());
    }
    p_new->setName(getName() + "_inv");
    return p_new;
}

void ParticleCoreShell::setAmbientMaterial(const IMaterial& material)
{
    mp_shell->setAmbientMaterial(material);
    mp_core->setAmbientMaterial(material);
}

const IMaterial *ParticleCoreShell::getAmbientMaterial() const
{
    if (!mp_shell) return 0;
    return mp_shell->getAmbientMaterial();
}

IFormFactor *ParticleCoreShell::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    if (mp_core==0 || mp_shell==0) return 0;
    FormFactorWeighted *p_result = new FormFactorWeighted;
    kvector_t zero_vector;
    boost::scoped_ptr<FormFactorDecoratorMaterial> P_ff_shell(
            getTransformedFormFactor(mp_shell, wavevector_scattering_factor,
                                     zero_vector) );
    if (P_ff_shell.get()==0) return 0;
    P_ff_shell->setAmbientMaterial(*getAmbientMaterial());
    p_result->addFormFactor(*P_ff_shell, 1.0);
    boost::scoped_ptr<FormFactorDecoratorMaterial> P_ff_core(
            getTransformedFormFactor(mp_core, wavevector_scattering_factor,
                                     m_relative_core_position) );
    if (P_ff_core.get()==0) return 0;
    P_ff_core->setAmbientMaterial(*mp_shell->getMaterial());
    p_result->addFormFactor(*P_ff_core, 1.0);
    return p_result;
}

void ParticleCoreShell::addAndRegisterCore(const Particle &core)
{
    if(mp_core) {
        deregisterChild(mp_core);
        delete mp_core;
    }
    mp_core = core.clone();
    registerChild(mp_core);
}


void ParticleCoreShell::addAndRegisterShell(const Particle &shell)
{
    if(mp_shell) {
        deregisterChild(mp_shell);
        delete mp_shell;
    }
    mp_shell = shell.clone();
    registerChild(mp_shell);
}

ParticleCoreShell::ParticleCoreShell(kvector_t relative_core_position)
: mp_shell(0)
, mp_core(0)
, m_relative_core_position(relative_core_position)
{
}

void ParticleCoreShell::applyTransformationToSubParticles(const IRotation& rotation)
{
    if (mp_core) {
        mp_core->applyTransformation(rotation);
    }
    if (mp_shell) {
        mp_shell->applyTransformation(rotation);
    }
    Geometry::Transform3D transform = rotation.getTransform3D();
    m_relative_core_position = transform.transformed(m_relative_core_position);
}

FormFactorDecoratorMaterial *ParticleCoreShell::getTransformedFormFactor(
        Particle *p_particle, complex_t wavevector_scattering_factor,
        kvector_t position) const
{
    if (p_particle->getFormFactor() == 0) return 0;
    const IRotation *p_rotation = p_particle->getRotation();
    IFormFactor *p_transf_ff = 0;
    if (p_rotation) {
        p_transf_ff = new FormFactorDecoratorTransformation(
                    p_particle->getFormFactor()->clone(), *p_rotation);
    } else {
        p_transf_ff = p_particle->getFormFactor()->clone();
    }
    IFormFactor *p_simple_ff = 0;
    kvector_t zero_vector;
    if (position == zero_vector) {
        p_simple_ff = p_transf_ff;
    } else {
        p_simple_ff = new FormFactorDecoratorPositionFactor(
                    *p_transf_ff, position);
        delete p_transf_ff;
    }
    FormFactorDecoratorMaterial *p_ff_result =
            new FormFactorDecoratorMaterial(p_simple_ff,
                                            wavevector_scattering_factor);
    if (p_rotation) {
        boost::scoped_ptr<const IMaterial> transformed_material(p_particle->
                getMaterial()->createTransformedMaterial(*p_rotation));
        p_ff_result->setMaterial(*transformed_material);
    } else {
        p_ff_result->setMaterial(*p_particle->getMaterial());
    }
    return p_ff_result;
}

