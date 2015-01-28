// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCone.h
//! @brief     Defines class FormFactorCone
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE_H
#define FORMFACTORCONE_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorCone
//! @ingroup formfactors
//! @brief The formfactor of a cone.

class BA_CORE_API_ FormFactorCone : public IFormFactorBorn
{
public:
    //! @brief Cone constructor
    //! @param radius of Cone's base
    //! @param height of Cone
    //! @param angle in radians between base and facet
    FormFactorCone(double radius, double height,  double alpha);
    ~FormFactorCone() {delete m_integrator;}

    virtual FormFactorCone* clone() const;

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
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorCone> *m_integrator;
};

#endif // FORMFACTORCONE_H


