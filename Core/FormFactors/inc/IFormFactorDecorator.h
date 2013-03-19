// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      FormFactors/IFormFactorDecorator.h 
//! @brief     Defines class IFormFactorDecorator.
//
// ************************************************************************** //

#ifndef IFORMFACTORDECORATOR_H_
#define IFORMFACTORDECORATOR_H_

#include "IFormFactor.h"

//! Encapsulates another formfactor and adds extra functionality (a scalar factor, a Debye-Waller factor, ...).

class IFormFactorDecorator : public IFormFactor
{
public:
    IFormFactorDecorator(IFormFactor *p_form_factor) : mp_form_factor(p_form_factor) {}
    virtual ~IFormFactorDecorator();
    virtual IFormFactorDecorator *clone() const=0;

    virtual void setAmbientRefractiveIndex(const complex_t &refractive_index);

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

inline void IFormFactorDecorator::setAmbientRefractiveIndex(const complex_t &refractive_index)
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
