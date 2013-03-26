// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorSphere.h
//! @brief     Defines class FormFactorSphere.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORSPHERE_H
#define FORMFACTORSPHERE_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"
#include "MemberComplexFunctionIntegrator.h"

//! Form factor of a sphere cut at given height.

class FormFactorSphere : public IFormFactorBorn
{
 public:
    FormFactorSphere(double radius, double height);

    ~FormFactorSphere() { delete m_integrator; }

    virtual FormFactorSphere *clone() const
    { return new FormFactorSphere(m_radius, m_height); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

 protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

 private:
    complex_t Integrand(double Z, void* params) const;

    //! register some class members for later access via parameter pool
    virtual void init_parameters();

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorSphere> *m_integrator;
};

#endif // FORMFACTORSPHERE_H
