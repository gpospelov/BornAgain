// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleCoreShell.h
//! @brief     Defines class ParticleCoreShell.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECORESHELL_H
#define PARTICLECORESHELL_H

#include "IParticle.h"

//! @class ParticleCoreShell
//! @ingroup samples
//! @brief A particle with a core/shell geometry

class BA_CORE_API_ ParticleCoreShell : public IParticle
{
public:
    ParticleCoreShell(const Particle& shell, const Particle& core,
            kvector_t relative_core_position);
    virtual ~ParticleCoreShell();
    virtual ParticleCoreShell *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleCoreShell *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences
    //! its scattering power)
    virtual void setAmbientMaterial(const IMaterial *p_material);
    virtual const IMaterial* getAmbientMaterial() const;

    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    //! Returns the core particle
    const Particle *getCoreParticle() const { return mp_core; }

    //! Returns the shell particle
    const Particle *getShellParticle() const { return mp_shell; }

    kvector_t getRelativeCorePosition() const { return m_relative_core_position; }

protected:
    void addAndRegisterCore(const Particle &core);
    void addAndRegisterShell(const Particle &shell);

    ParticleCoreShell(kvector_t relative_core_position);
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform);
    FormFactorDecoratorMaterial *getTransformedFormFactor(
            Particle *p_particle, complex_t wavevector_scattering_factor,
            kvector_t position) const;
    Particle *mp_shell;
    Particle *mp_core;
    kvector_t m_relative_core_position;
};

#endif // PARTICLECORESHELL_H


