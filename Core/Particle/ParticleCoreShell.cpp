// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleCoreShell.cpp
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
#include "BornAgainNamespace.h"
#include "FormFactorCoreShell.h"
#include "HomogeneousMaterial.h"
#include "Particle.h"

ParticleCoreShell::ParticleCoreShell(
    const Particle& shell, const Particle& core, kvector_t relative_core_position)
{
    setName(BornAgain::ParticleCoreShellType);
    registerParticleProperties();
    addAndRegisterCore(core, relative_core_position);
    addAndRegisterShell(shell);
}

ParticleCoreShell::~ParticleCoreShell()
{
}

ParticleCoreShell* ParticleCoreShell::clone() const
{
    ParticleCoreShell* p_result = new ParticleCoreShell(*mp_shell, *mp_core);
    p_result->setAbundance(m_abundance);
    if (mP_rotation.get())
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

ParticleCoreShell* ParticleCoreShell::cloneInvertB() const
{
    ParticleCoreShell* p_result = new ParticleCoreShell();
    p_result->setAbundance(m_abundance);
    p_result->mp_shell.reset(mp_shell->cloneInvertB());
    p_result->mp_core.reset(mp_core->cloneInvertB());
    if (mP_rotation.get())
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

IFormFactor* ParticleCoreShell::createSlicedFormFactor(ZLimits limits) const
{
    if (!mp_core || !mp_shell)
        return nullptr;
    std::unique_ptr<IRotation> P_rotation(IRotation::createIdentity());
    if (mP_rotation)
        P_rotation.reset(mP_rotation->clone());

    // core form factor
    std::unique_ptr<Particle> P_core(mp_core->clone());
    P_core->applyRotation(*P_rotation);
    P_core->applyTranslation(m_position);
    std::unique_ptr<IFormFactor> P_ff_core(P_core->createSlicedFormFactor(limits) );
    if (!P_ff_core)
        return nullptr;

    // shell form factor
    std::unique_ptr<Particle> P_shell(mp_shell->clone());
    P_shell->applyRotation(*P_rotation);
    P_shell->applyTranslation(m_position);
    std::unique_ptr<IFormFactor> P_ff_shell(P_shell->createSlicedFormFactor(limits) );
    if (!P_ff_shell)
        return nullptr;

    // set core ambient material (needs to be rotated separately, AFTER applying
    // ParticleCoreShell's rotation to the clone of the shell particle)
    const HomogeneousMaterial* p_shell_material = P_shell->material();
    if (p_shell_material) {
        const std::unique_ptr<const HomogeneousMaterial> P_transformed_material(
                    p_shell_material->createTransformedMaterial(
                        P_shell->rotation()->getTransform3D()));
        P_ff_core->setAmbientMaterial(*P_transformed_material);
    }

    return new FormFactorCoreShell(P_ff_core.release(), P_ff_shell.release());
}

std::vector<const INode*> ParticleCoreShell::getChildren() const
{
    return std::vector<const INode*>() << IParticle::getChildren() << mp_core << mp_shell;
}

void ParticleCoreShell::addAndRegisterCore(const Particle& core,
                                           kvector_t relative_core_position)
{
    mp_core.reset(core.clone());
    mp_core->applyTranslation(relative_core_position);
    registerChild(mp_core.get());
    mp_core->registerAbundance(false);
}

void ParticleCoreShell::addAndRegisterShell(const Particle& shell)
{
    mp_shell.reset(shell.clone());
    registerChild(mp_shell.get());
    mp_shell->registerAbundance(false);
    mp_shell->registerPosition(false);
}

ParticleCoreShell::ParticleCoreShell()
    : mp_shell { nullptr }, mp_core { nullptr }
{
    setName(BornAgain::ParticleCoreShellType);
}
