// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleCoreShell.h
//! @brief     Defines class ParticleCoreShell.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECORESHELL_H
#define PARTICLECORESHELL_H

#include "Particle.h"

//! A particle with a core/shell geometry

class ParticleCoreShell : public Particle
{
 public:
    ParticleCoreShell(const Particle& shell, const Particle& core, kvector_t relative_core_position);
    virtual ~ParticleCoreShell();
    virtual ParticleCoreShell *clone() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) const { p_visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its scattering power)
    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        m_ambient_refractive_index = refractive_index;
        mp_shell->setAmbientRefractiveIndex(refractive_index);
        mp_core->setAmbientRefractiveIndex(refractive_index);
    }

    virtual IFormFactor* createFormFactor() const;

    //! Sets the formfactor of the particle (not including scattering factor from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor)
    {
        if (p_form_factor != mp_form_factor) {
            deregisterChild(mp_form_factor);
            delete mp_form_factor;
            mp_form_factor = p_form_factor;
            registerChild(mp_form_factor);
        }
    }

    //! Returns formfactor of the particle (not including scattering factor from refractive index)
    virtual const IFormFactor *getSimpleFormFactor() const { return mp_form_factor;}

    //! Creates list of contained particles for diffuse calculations
    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(const ParticleInfo& parent_info) const {
        (void)parent_info;
        return 0;
    }

 protected:
    Particle *mp_shell;
    Particle *mp_core;
    kvector_t m_relative_core_position;
};

#endif // PARTICLECORESHELL_H


