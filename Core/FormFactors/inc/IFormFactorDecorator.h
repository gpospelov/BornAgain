#ifndef IFORMFACTORDECORATOR_H_
#define IFORMFACTORDECORATOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFormFactorDecorator.h
//! @brief  Definition of IFormFactorDecorator class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 28, 2012

#include "IFormFactor.h"

//- -------------------------------------------------------------------
//! @class IFormFactorDecorator
//! @brief Definition of IFormFactorDecorator interface
//!
//! IFormFactorDecorator encapsulates another formfactor and adds
//! extra functionality to it (a scalar factor, a Debye-Waller factor, ...)
//- -------------------------------------------------------------------
class IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor) : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator();
    virtual IFormFactorDecorator *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

    virtual double getVolume() const;

    virtual double getHeight() const;

    virtual double getRadius() const;

protected:
    IFormFactor *mp_form_factor;
};

inline IFormFactorDecorator::~IFormFactorDecorator()
{
    delete mp_form_factor;
}

inline void IFormFactorDecorator::setAmbientRefractiveIndex(complex_t refractive_index)
{
    if (mp_form_factor) mp_form_factor->setAmbientRefractiveIndex(refractive_index);
}

inline double IFormFactorDecorator::getVolume() const
{
    if (mp_form_factor) {
        return mp_form_factor->getVolume();
    }
    return 0.0;
}

inline double IFormFactorDecorator::getHeight() const
{
    if (mp_form_factor) {
        return mp_form_factor->getHeight();
    }
    return 0.0;
}

inline double IFormFactorDecorator::getRadius() const
{
    if (mp_form_factor) {
        return mp_form_factor->getRadius();
    }
    return 0.0;
}

#endif /* IFORMFACTORDECORATOR_H_ */
