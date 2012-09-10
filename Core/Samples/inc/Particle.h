#ifndef NANOPARTICLE_H
#define NANOPARTICLE_H
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

class DiffuseNanoParticleInfo;
//- -------------------------------------------------------------------
//! @class NanoParticle
//! @brief Definition of a nanoparticle with a form factor
//- -------------------------------------------------------------------
class Particle : public ICompositeSample
{
public:
    Particle(complex_t refractive_index, IFormFactor* p_form_factor = 0);
    Particle(complex_t refractive_index, const IFormFactor &p_form_factor);
    virtual ~Particle();
    virtual Particle *clone() const;

//    virtual complex_t getRefractiveIndex() const
//    {
//        return m_refractive_index;
//    }

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

    virtual void setFormFactor(IFormFactor* p_form_factor)
    {
        if (p_form_factor != mp_form_factor) {
            delete mp_form_factor;
            mp_form_factor = p_form_factor;
        }
    }

    //! return form factor of the particle
    const IFormFactor *getFormFactor() const { return mp_form_factor;}

    //! create list of contained nanoparticles for diffuse calculations
    virtual std::vector<DiffuseNanoParticleInfo *> *createDiffuseNanoParticleInfo(double depth, double weight,
            const Geometry::Transform3D &transform) const {
        (void)depth;
        (void)weight;
        (void)transform;
        return 0;
    }

protected:
    complex_t m_ambient_refractive_index;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    Particle(const Particle &);
    Particle &operator=(const Particle &);

    complex_t m_refractive_index;
    IFormFactor* mp_form_factor;
    ///< pointer to the form factor
};

#endif // NANOPARTICLE_H
