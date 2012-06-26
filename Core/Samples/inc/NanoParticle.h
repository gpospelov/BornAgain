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

    complex_t getRefractiveIndex() const
    {
        return m_refractive_index;
    }

    void setRefractiveIndex(complex_t refractiveIndex)
    {
        m_refractive_index = refractiveIndex;
    }

    const IFormFactor* getFormFactor() const
    {
        return mp_form_factor;
    }

    void setFormFactor(IFormFactor* mpFormFactor)
    {
        mp_form_factor = mpFormFactor;
    }

private:
    complex_t m_refractive_index;
    IFormFactor* mp_form_factor;
    ///< pointer to the form factor
};

#endif // NANOPARTICLE_H
