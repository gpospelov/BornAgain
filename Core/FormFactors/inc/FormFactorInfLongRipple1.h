// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorRipple1.h
//! @brief     Defines class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORINFLONGRIPPLE1_H
#define FORMFACTORINFLONGRIPPLE1_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorInfLongRipple1
//! @ingroup formfactors
//! @brief The formfactor for an infinitely long cosine ripple.

class BA_CORE_API_ FormFactorInfLongRipple1 : public IFormFactorBorn
{
public:
    //! @brief InfLongRipple1 constructor
    //! @param width of cosine cross section
    //! @param height of cosine cross section
    FormFactorInfLongRipple1(double width, double height);

    virtual ~FormFactorInfLongRipple1() { delete m_integrator; }

    virtual FormFactorInfLongRipple1 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getWidth() const { return m_width; }

    virtual double getHeight() const { return m_height; }

    virtual double getRadius() const { return 0.5*m_width; }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

    double getVolume() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double Z, void* params) const;

    double m_width;
    double m_height;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorInfLongRipple1> *m_integrator;
};

#endif // FORMFACTORINFLONGRIPPLE1_H


