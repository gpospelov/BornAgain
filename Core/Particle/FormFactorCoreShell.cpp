// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCoreShell.cpp
//! @brief     Implements class FormFactorCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCoreShell.h"
#include "BornAgainNamespace.h"


FormFactorCoreShell::FormFactorCoreShell(IFormFactor* core, IFormFactor* shell)
    : mP_core(core)
    , mP_shell(shell)
{
    setName(BornAgain::FormFactorCoreShellType);
}

FormFactorCoreShell::~FormFactorCoreShell()
{}

FormFactorCoreShell*FormFactorCoreShell::clone() const
{
    return new FormFactorCoreShell(mP_core->clone(), mP_shell->clone());
}

double FormFactorCoreShell::getRadialExtension() const
{
    return mP_shell->getRadialExtension();
}

double FormFactorCoreShell::bottomZ(const IRotation& rotation) const
{
    return mP_shell->bottomZ(rotation);
}

double FormFactorCoreShell::topZ(const IRotation& rotation) const
{
    return mP_shell->topZ(rotation);
}

void FormFactorCoreShell::setAmbientMaterial(HomogeneousMaterial material)
{
    mP_shell->setAmbientMaterial(material);
}

complex_t FormFactorCoreShell::evaluate(const WavevectorInfo& wavevectors) const
{
    return mP_shell->evaluate(wavevectors) + mP_core->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorCoreShell::evaluatePol(const WavevectorInfo& wavevectors) const
{
    return mP_shell->evaluatePol(wavevectors) + mP_core->evaluatePol(wavevectors);
}
