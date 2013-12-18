// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorRipple2.h
//! @brief     Defines class FormFactorRipple2.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE2_H
#define FORMFACTORRIPPLE2_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorRipple2
//! @ingroup formfactors
//! @brief The formfactor for a triangular ripple.

class BA_CORE_API_ FormFactorRipple2 : public IFormFactorBorn
{
public:
    FormFactorRipple2(double width, double height, double length, double asymetry);

    ~FormFactorRipple2() { delete m_integrator; }

    virtual FormFactorRipple2 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 4; }

    virtual double getHeight() const { return m_height; }
    virtual double getWidth() const { return m_width; }
    virtual double getLength() const { return m_length; }
    virtual double getAsymetry() const { return m_d; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t& q) const;

private:
    complex_t Integrand(double Z, void* params) const;

    virtual void init_parameters();

    double m_width;
    double m_height;
    double m_length;
    double m_d;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorRipple2> *m_integrator;
};

#endif // FORMFACTORSPHERE_H


