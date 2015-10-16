// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorRipple2.h
//! @brief     Defines class FormFactorRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORINFLONGRIPPLE2_H
#define FORMFACTORINFLONGRIPPLE2_H

#include "IFormFactorBorn.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorInfLongRipple2
//! @ingroup formfactors
//! @brief The formfactor for an infinitely long triangular ripple.

class BA_CORE_API_ FormFactorInfLongRipple2 : public IFormFactorBorn
{
public:
    //! @brief InfLongRipple2 constructor
    //! @param width of triangular cross section
    //! @param height of triangular cross section
    //! @param asymmetry length of triangular cross section
    FormFactorInfLongRipple2(double width, double height, double asymetry);

    virtual ~FormFactorInfLongRipple2() { }

    virtual FormFactorInfLongRipple2 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }
    virtual double getWidth() const { return m_width; }
    virtual double getAsymetry() const { return m_d; }

    virtual double getRadius() const { return 0.5*m_width; }

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;
    double getVolume() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_width;
    double m_height;
    double m_d;
    mutable cvector_t m_q;
};

#endif // FORMFACTORINFLONGRIPPLE2_H


