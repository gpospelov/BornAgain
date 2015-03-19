// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTruncatedSphere.h
//! @brief     Defines class FormFactorTruncatedSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDSPHERE_H
#define FORMFACTORTRUNCATEDSPHERE_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorTruncatedSphere
//! @ingroup formfactors
//! @brief The formfactor of a truncated Sphere.

class BA_CORE_API_ FormFactorTruncatedSphere : public IFormFactorBorn
{
public:
    //! @brief TruncatedSphere constructor
    //! @param radius of Truncated Sphere
    //! @param height of Truncated Sphere
    FormFactorTruncatedSphere(double radius, double height);

    ~FormFactorTruncatedSphere() { delete m_integrator; }

    virtual FormFactorTruncatedSphere *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();
    virtual complex_t evaluate_for_q(const cvector_t& q) const;

private:
    complex_t Integrand(double Z, void* params) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorTruncatedSphere> *m_integrator;
};

#endif // FORMFACTORTRUNCATEDSPHERE_H


