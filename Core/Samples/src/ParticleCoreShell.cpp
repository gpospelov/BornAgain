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
{
    setName("ParticleCoreShell");
    registerParameter("position_x", &m_position[0]);
    registerParameter("position_y", &m_position[1]);
    registerParameter("position_z", &m_position[2]);
    addAndRegisterCore(core, relative_core_position);
    addAndRegisterShell(shell);
}

ParticleCoreShell::~ParticleCoreShell()
{
    delete mp_shell;
    delete mp_core;
}

ParticleCoreShell *ParticleCoreShell::clone() const
{
    ParticleCoreShell *p_new = new ParticleCoreShell(*mp_shell, *mp_core, kvector_t(0.0, 0.0, 0.0));
    p_new->setAmbientMaterial(*getAmbientMaterial());
    if (mP_rotation.get()) {
        p_new->setRotation(*mP_rotation);
    }
    p_new->setPosition(m_position);
    p_new->setName(getName());
    return p_new;
}

ParticleCoreShell* ParticleCoreShell::cloneInvertB() const
{
    ParticleCoreShell *p_new = new ParticleCoreShell();
    p_new->mp_shell = this->mp_shell->cloneInvertB();
    p_new->mp_core = this->mp_core->cloneInvertB();
    p_new->setAmbientMaterial( *Materials::createInvertedMaterial(getAmbientMaterial()) );
    if (mP_rotation.get()) {
        p_new->setRotation(*mP_rotation);
    }
    p_new->setPosition(m_position);
    p_new->setName(getName() + "_inv");
    return p_new;
}

void ParticleCoreShell::setAmbientMaterial(const IMaterial& material)
{
    mp_shell->setAmbientMaterial(material);
}

const IMaterial *ParticleCoreShell::getAmbientMaterial() const
{
    if (!mp_shell) return 0;
    return mp_shell->getAmbientMaterial();
}

IFormFactor *ParticleCoreShell::createTransformedFormFactor(complex_t wavevector_scattering_factor,
    const IRotation *p_rotation, kvector_t translation) const
{
    if (mp_core==0 || mp_shell==0) return 0;
    FormFactorWeighted *p_result = new FormFactorWeighted();
    boost::scoped_ptr<IRotation> P_total_rotation(createComposedRotation(p_rotation));
    kvector_t total_position = getComposedTranslation(p_rotation, translation);
    // shell form factor
    boost::scoped_ptr<IFormFactor> P_ff_shell(
            mp_shell->createTransformedFormFactor(wavevector_scattering_factor,
                           P_total_rotation.get(), total_position) );
    if (P_ff_shell.get()==0) return 0;
    p_result->addFormFactor(*P_ff_shell, 1.0);
    // core form factor
    boost::scoped_ptr<Particle> P_core_clone(mp_core->clone());
    P_core_clone->setAmbientMaterial(*mp_shell->getMaterial());
    boost::scoped_ptr<IFormFactor> P_ff_core(
                P_core_clone->createTransformedFormFactor(wavevector_scattering_factor,
                               P_total_rotation.get(), total_position) );
    if (P_ff_core.get()==0) return 0;
    p_result->addFormFactor(*P_ff_core, 1.0);
    return p_result;
}

void ParticleCoreShell::addAndRegisterCore(const Particle &core, kvector_t relative_core_position)
{
    if(mp_core) {
        deregisterChild(mp_core);
        delete mp_core;
    }
    mp_core = core.clone();
    mp_core->applyTranslation(relative_core_position);
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

ParticleCoreShell::ParticleCoreShell()
: mp_shell(0)
, mp_core(0)
{
}
