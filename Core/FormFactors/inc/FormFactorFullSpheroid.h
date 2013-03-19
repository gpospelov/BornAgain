// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorFullSpheroid.h
//! @brief     Defines class FormFactorFullSpheroid.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHEROID_H
#define FORMFACTORFULLSPHEROID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! ?

class FormFactorFullSpheroid : public IFormFactorBorn
{
public:
    FormFactorFullSpheroid(double radius, double height);
    double FullSpheroidIntegral(double Z, void* params) const;
    ~FormFactorFullSpheroid();
    virtual FormFactorFullSpheroid *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();
private:

    double evaluate_for_q_real() const;
    complex_t evaluate_for_q_imag() const;
    double FullSpheroidIntegralReal(double Z, void* params) const;
    double FullSpheroidIntegralImaginary(double Z, void* params) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

};

#endif // FORMFACTORFULLSPHEROID_H
