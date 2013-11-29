// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ParticleCoreShell.cpp
//! @brief     Implements class ParticleCoreShell.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCoreShell.h"
#include "FormFactors.h"
#include "MaterialManager.h"

ParticleCoreShell::ParticleCoreShell(const Particle& shell,
        const Particle& core, kvector_t relative_core_position)
    : m_relative_core_position(relative_core_position)
{
    mp_shell = shell.clone();
    mp_core = core.clone();
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
    p_new->setAmbientMaterial(mp_ambient_material);
    return p_new;
}

ParticleCoreShell* ParticleCoreShell::cloneInvertB() const
{
    ParticleCoreShell *p_new = new ParticleCoreShell(m_relative_core_position);
    p_new->mp_shell = this->mp_shell->cloneInvertB();
    p_new->mp_core = this->mp_core->cloneInvertB();
    const IMaterial *p_ambient_material = MaterialManager::getInvertedMaterial(
            this->mp_ambient_material->getName());
    p_new->setAmbientMaterial(p_ambient_material);
    return p_new;
}

void ParticleCoreShell::setAmbientMaterial(const IMaterial* p_material)
{
    mp_ambient_material = p_material;
    mp_shell->setAmbientMaterial(p_material);
    mp_core->setAmbientMaterial(p_material);
}

IFormFactor *ParticleCoreShell::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    FormFactorWeighted *p_result = new FormFactorWeighted;
    FormFactorDecoratorMaterial ff_shell(mp_shell->
            getSimpleFormFactor()->clone(),
            wavevector_scattering_factor);
    if (mP_transform.get()) {
        boost::scoped_ptr<const IMaterial> transformed_material_shell(mp_shell->
                getMaterial()->createTransformedMaterial(*mP_transform));
        ff_shell.setMaterial(transformed_material_shell.get());
    } else {
        ff_shell.setMaterial(mp_shell->getMaterial());
    }
    ff_shell.setAmbientMaterial(mp_ambient_material);
    p_result->addFormFactor(ff_shell, 1.0);
    IFormFactor *p_core_simple = new FormFactorDecoratorPositionFactor(
            *mp_core->getSimpleFormFactor(), m_relative_core_position);
    FormFactorDecoratorMaterial ff_core(p_core_simple,
            wavevector_scattering_factor);
    if (mP_transform.get()) {
        boost::scoped_ptr<const IMaterial> transformed_material_core(mp_core->
                getMaterial()->createTransformedMaterial(*mP_transform));
        ff_core.setMaterial(transformed_material_core.get());
    } else {
        ff_core.setMaterial(mp_shell->getMaterial());
    }
    ff_core.setAmbientMaterial(mp_shell->getMaterial());
    p_result->addFormFactor(ff_core, 1.0);
    return p_result;
}

void ParticleCoreShell::setSimpleFormFactor(IFormFactor* p_form_factor)
{
    if (p_form_factor != mp_form_factor) {
        deregisterChild(mp_form_factor);
        delete mp_form_factor;
        mp_form_factor = p_form_factor;
        registerChild(mp_form_factor);
    }
}

ParticleCoreShell::ParticleCoreShell(kvector_t relative_core_position)
: mp_shell(0)
, mp_core(0)
, m_relative_core_position(relative_core_position)
{
}
