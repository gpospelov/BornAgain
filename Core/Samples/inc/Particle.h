#ifndef PARTICLE_H
#define PARTICLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Particle.h
//! @brief  Definition of Particle class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "FormFactorDecoratorRefractiveIndex.h"

class DiffuseParticleInfo;
class ParticleInfo;

//- -------------------------------------------------------------------
//! @class Particle
//! @brief Definition of a particle with a form factor and refractive index
//- -------------------------------------------------------------------
class Particle : public ICompositeSample
{
public:
    Particle(complex_t refractive_index, IFormFactor* p_form_factor = 0);
    Particle(complex_t refractive_index, const IFormFactor &p_form_factor);
    virtual ~Particle();
    virtual Particle *clone() const;

    //! Set the refractive index of the ambient material (which influences its scattering power)
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

    //! set the form factor of the particle (not including scattering factor from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor)
    {
        if (p_form_factor != mp_form_factor) {
            delete mp_form_factor;
            mp_form_factor = p_form_factor;
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
    complex_t m_ambient_refractive_index;
    complex_t m_refractive_index;
    IFormFactor* mp_form_factor;
    //!< pointer to the form factor

private:
    //! copy constructor and assignment operator are absent
    Particle(const Particle &);
    Particle &operator=(const Particle &);

};

#endif // PARTICLE_H
