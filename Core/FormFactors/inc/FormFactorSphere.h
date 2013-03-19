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
//! @file      FormFactors/FormFactorSphere.h 
//! @brief     Defines class FormFactorSphere.
//
// ************************************************************************** //

#ifndef FORMFACTORSPHERE_H
#define FORMFACTORSPHERE_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"
#include "MemberComplexFunctionIntegrator.h"

//! Form factor of a sphere.

class FormFactorSphere : public IFormFactorBorn
{
public:
    FormFactorSphere(double radius, double height);
    double SphereIntegral(double Z, void* params) const;

    ~FormFactorSphere();
    virtual FormFactorSphere *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    complex_t Integrand(double Z, void* params) const;

//    double evaluate_for_q_real() const;
//    double evaluate_for_q_imag() const;
//    double SphereIntegralImaginary(double Z, void* params) const;
//    double SphereIntegralReal(double Z, void* params) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorSphere> *m_integrator;
};

#endif // FORMFACTORSPHERE_H
