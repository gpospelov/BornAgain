#ifndef PARTICLECORESHELL_H
#define PARTICLECORESHELL_H

// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ParticleCoreShell.h
//! @brief  Definition of ParticleCoreShell class
//! @author Scientific Computing Group at FRM II
//! @date  1/10/12

#include "Particle.h"

//- -------------------------------------------------------------------
//! @class ParticleCoreShell
//! @brief Describes a particle with a core/shell geometry
//- -------------------------------------------------------------------
class ParticleCoreShell : public Particle
{
public:
    ParticleCoreShell(const Particle &shell, const Particle &core, kvector_t relative_core_position);
    virtual ~ParticleCoreShell();
    virtual ParticleCoreShell *clone() const;

    //! Set the refractive index of the ambient material (which influences its scattering power)
    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        m_ambient_refractive_index = refractive_index;
        mp_shell->setAmbientRefractiveIndex(refractive_index);
        mp_core->setAmbientRefractiveIndex(refractive_index);
    }

    virtual IFormFactor* createFormFactor() const;

    //! set the form factor of the particle (not including scattering factor from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor)
    {
        if (p_form_factor != mp_form_factor) {
            deregisterChild(mp_form_factor);
            delete mp_form_factor;
            mp_form_factor = p_form_factor;
            registerChild(mp_form_factor);
        }
    }

    //! return form factor of the particle (not including scattering factor from refractive index)
    virtual const IFormFactor *getSimpleFormFactor() const { return mp_form_factor;}

    //! create list of contained particles for diffuse calculations
    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(const ParticleInfo &parent_info) const {
        (void)parent_info;
        return 0;
    }

protected:
    Particle *mp_shell;
    Particle *mp_core;
    kvector_t m_relative_core_position;
};

#endif // PARTICLECORESHELL_H
