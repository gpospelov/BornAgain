// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "FormFactorDecoratorRefractiveIndex.h"

class DiffuseParticleInfo;
class ParticleInfo;

//! A particle with a form factor and refractive index

class Particle : public ICompositeSample
{
 public:
    Particle(const complex_t& refractive_index, IFormFactor* p_form_factor = 0);
    Particle(const complex_t& refractive_index, const IFormFactor& form_factor);
    virtual ~Particle();
    virtual Particle *clone() const;

    //! Sets the refractive index of the ambient material (which influences its scattering power)
    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        m_ambient_refractive_index = refractive_index;
    }

    virtual IFormFactor* createFormFactor() const
    {
        FormFactorDecoratorRefractiveIndex *p_ff = new FormFactorDecoratorRefractiveIndex(
                mp_form_factor->clone(), m_refractive_index);
        p_ff->setAmbientRefractiveIndex(m_ambient_refractive_index);
        return p_ff;
    }

    //! Sets the form factor of the particle (not including scattering factor from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor)
    {
        if (p_form_factor != mp_form_factor) {
            deregisterChild(mp_form_factor);
            delete mp_form_factor;
            mp_form_factor = p_form_factor;
            registerChild(mp_form_factor);
        }
    }

    //! Returns refractive index of the particle
    virtual const complex_t getRefractiveIndex() const {
        return m_refractive_index;
    }

    //! Returns formfactor of the particle (not including scattering factor from refractive index)
    virtual const IFormFactor *getSimpleFormFactor() const { return mp_form_factor;}

    //! Creates list of contained particles for diffuse calculations
    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(const ParticleInfo& parent_info) const {
        (void)parent_info;
        return 0;
    }

    virtual bool hasDistributedFormFactor() const { return mp_form_factor->isDistributedFormFactor(); }

    virtual std::vector<ParticleInfo *> createDistributedParticles(size_t samples_per_particle, double factor) const;

 protected:
    complex_t m_ambient_refractive_index;
    complex_t m_refractive_index;
    IFormFactor* mp_form_factor;
    //!< pointer to the form factor
};

#endif // PARTICLE_H
