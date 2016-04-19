// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorLongRipple1Gauss.h
//! @brief     Declares class FormFactorLongRipple1Gauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLONGRIPPLE1GAUSS_H
#define FORMFACTORLONGRIPPLE1GAUSS_H

#include "IFormFactorBorn.h"

#include <memory>

// Forward declaration to prevent IntegratorComplex.h to be parsed for Python API:
template <class T> class IntegratorComplex;

//! @class FormFactorLongRipple1Gauss
//! @ingroup formfactors
//! @brief The formfactor for a cosine ripple.

class BA_CORE_API_ FormFactorLongRipple1Gauss : public IFormFactorBorn
{
public:
    //! @brief Ripple1 constructor
    //! @param length of Ripple1
    //! @param width of cosine cross section
    //! @param height of cosine cross section
    FormFactorLongRipple1Gauss(double length, double width, double height);

    virtual ~FormFactorLongRipple1Gauss();

    virtual FormFactorLongRipple1Gauss *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    double getHeight() const;

    double getWidth() const;

    double getLength() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double Z) const;

    double m_width;
    double m_height;
    double m_length;
    mutable cvector_t m_q;

#ifndef GCCXML_SKIP_THIS
    std::unique_ptr<IntegratorComplex<FormFactorLongRipple1Gauss>> mP_integrator;
#endif
};

inline double FormFactorLongRipple1Gauss::getHeight() const
{
    return m_height;
}

inline double FormFactorLongRipple1Gauss::getWidth() const
{
    return m_width;
}

inline double FormFactorLongRipple1Gauss::getLength() const
{
    return m_length;
}

#endif // FORMFACTORLONGRIPPLE1GAUSS_H


