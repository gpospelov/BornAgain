// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorCoreShell.h
//! @brief     Defines class FormFactorCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCORESHELL_H
#define FORMFACTORCORESHELL_H

#include "IFormFactor.h"

#include <memory>

//! Form Factor for a core shell particle.
//!
//! Used by ParticleCoreShell.

//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorCoreShell : public IFormFactor
{
public:
    FormFactorCoreShell(IFormFactor* core, IFormFactor* shell);
    ~FormFactorCoreShell() override final;

    FormFactorCoreShell* clone() const override final;

    void accept(INodeVisitor* visitor) const override  final { visitor->visit(this); }

    double getRadialExtension() const override final;

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    void setAmbientMaterial(const IMaterial& material) override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;

#ifndef SWIG
    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

protected:
    std::unique_ptr<IFormFactor> mP_core;
    std::unique_ptr<IFormFactor> mP_shell;
};

#endif // FORMFACTORCORESHELL_H
