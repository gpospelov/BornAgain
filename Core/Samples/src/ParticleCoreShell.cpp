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

IFormFactor *ParticleCoreShell::createFormFactor(
        complex_t wavevector_scattering_factor) const
{
    FormFactorWeighted *p_result = new FormFactorWeighted;
    FormFactorDecoratorMaterial ff_shell(mp_shell->
            getSimpleFormFactor()->clone(),
            wavevector_scattering_factor);
    ff_shell.setMaterial(mp_shell->getMaterial());
    ff_shell.setAmbientMaterial(mp_ambient_material);
    p_result->addFormFactor(ff_shell, 1.0);
    FormFactorDecoratorMaterial ff_core(mp_core->getSimpleFormFactor()->
            clone(),
            wavevector_scattering_factor);
    ff_core.setMaterial(mp_core->getMaterial());
    ff_core.setAmbientMaterial(mp_shell->getMaterial());
    FormFactorDecoratorPositionFactor ff_core_translated(ff_core,
            m_relative_core_position);
    p_result->addFormFactor(ff_core_translated, 1.0);
    return p_result;
}

ParticleCoreShell::ParticleCoreShell(kvector_t relative_core_position)
: mp_shell(0)
, mp_core(0)
, m_relative_core_position(relative_core_position)
{
}
