// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTetrahedron.h
//! @brief     Defines class FormFactorTetrahedron
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTETRAHEDRON_H
#define FORMFACTORTETRAHEDRON_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"
// addition integration
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorTetrahedron
//! @ingroup formfactors
//! @brief The formfactor of tetrahedron.

class BA_CORE_API_ FormFactorTetrahedron : public IFormFactorBorn
{
public:
    //! @brief Tetrahedron constructor
    //! @param length of a side of Tetrahedron's base
    //! @param height of Tetrahedron
    //! @param angle in radians between base and facet
    FormFactorTetrahedron(double length, double height, double alpha);
    //~FormFactorTetrahedron() {}
    // addition integration
    ~FormFactorTetrahedron() {delete m_integrator;}

    virtual FormFactorTetrahedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getLength() const { return m_length; }
    virtual void setLength(double length) { m_length = length; }

    virtual double getAlpha() const { return m_alpha; }
    virtual void setAlpha(double alpha) { m_alpha = alpha; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:

    double m_height;
    double m_length;
    double m_alpha;
    double m_root3; // Cached value of square root of 3

    // addition integration
    mutable cvector_t m_q;
    complex_t Integrand(double Z, void* params) const;
    MemberComplexFunctionIntegrator<FormFactorTetrahedron> *m_integrator;

};

#endif // FORMFACTORTETRAHEDRON_H
