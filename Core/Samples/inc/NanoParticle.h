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
//! @file   NanoParticle.h
//! @brief  Definition of NanoParticle
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "ISample.h"
#include "IFormFactor.h"
#include "FormFactorDecoratorRefractiveIndex.h"


//- -------------------------------------------------------------------
//! @class NanoParticle
//! @brief Definition of a nanoparticle with a form factor
//- -------------------------------------------------------------------
class NanoParticle : public ISample
{
public:
    NanoParticle(complex_t refractive_index, IFormFactor* p_form_factor = 0);
    virtual ~NanoParticle();
    virtual NanoParticle *clone() const;

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

protected:
    complex_t m_ambient_refractive_index;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    NanoParticle(const NanoParticle &);
    NanoParticle &operator=(const NanoParticle &);

    complex_t m_refractive_index;
    IFormFactor* mp_form_factor;
    ///< pointer to the form factor
};

#endif // NANOPARTICLE_H
