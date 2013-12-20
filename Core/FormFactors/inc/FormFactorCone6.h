// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCone6.h
//! @brief     Defines class FormFactorCone6
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE6_H
#define FORMFACTORCONE6_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorCone6
//! @ingroup formfactors
//! @brief The formfactor of a cone6.

class BA_CORE_API_ FormFactorCone6 : public IFormFactorBorn
{
public:
    //! @brief cone6 constructor
    //! @param radius of hexagonal base (different from R in IsGisaxs)
    //! @param height of cone6
    //! @param angle in radians between base and facet
    FormFactorCone6(double radius, double height,  double alpha);
    ~FormFactorCone6() {delete m_integrator;}

    virtual FormFactorCone6* clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getRadius() const { return m_radius; }
    virtual void setRadius(double radius) { m_radius = radius; }

    virtual double getAlpha() const { return m_alpha; }
    virtual void setAlpha(double alpha) { m_alpha = alpha; }

    virtual complex_t evaluate_for_q (const cvector_t& q) const;

protected:

    virtual void init_parameters();

private:

    complex_t Integrand(double Z, void* params) const;

    double m_radius;
    double m_height;
    double m_alpha;
    double m_root3; // Cached value of square root of 3
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorCone6> *m_integrator;
};

#endif // FORMFACTORCONE6_H


