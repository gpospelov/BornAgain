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

ParticleCoreShell::ParticleCoreShell(const Particle& shell, const Particle& core, kvector_t relative_core_position)
: Particle(shell.getRefractiveIndex())
, m_relative_core_position(relative_core_position)
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
    ParticleCoreShell *p_new = new ParticleCoreShell(*mp_shell, *mp_core, m_relative_core_position);
    p_new->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_new;
}

IFormFactor *ParticleCoreShell::createFormFactor() const
{
    FormFactorWeighted *p_result = new FormFactorWeighted;
    FormFactorDecoratorRefractiveIndex ff_shell(mp_shell->getSimpleFormFactor()->clone(),
            mp_shell->getRefractiveIndex());
    ff_shell.setAmbientRefractiveIndex(m_ambient_refractive_index);
    p_result->addFormFactor(ff_shell, 1.0);
    complex_t core_index = std::sqrt(mp_core->getRefractiveIndex()*mp_core->getRefractiveIndex()
            - mp_shell->getRefractiveIndex()*mp_shell->getRefractiveIndex()
            + m_ambient_refractive_index*m_ambient_refractive_index);
    FormFactorDecoratorRefractiveIndex ff_core(mp_core->getSimpleFormFactor()->clone(),
            core_index);
    ff_core.setAmbientRefractiveIndex(m_ambient_refractive_index);
    FormFactorDecoratorPositionFactor ff_core_translated(ff_core, m_relative_core_position);
    p_result->addFormFactor(ff_core_translated, 1.0);
    return p_result;
}


