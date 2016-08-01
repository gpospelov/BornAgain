// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple1.h
//! @brief     Declares class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE1_H
#define FORMFACTORRIPPLE1_H

#include "IFormFactorBorn.h" // inheriting from
#include "IntegratorComplex.h"

//! @class FormFactorRipple1
//! @ingroup formfactors
//! @brief The formfactor for a cosine ripple.

class BA_CORE_API_ FormFactorRipple1 : public IFormFactorBorn
{
public:
    //! @brief Ripple1 constructor
    //! @param length of Ripple1
    //! @param width of cosine cross section
    //! @param height of cosine cross section
    FormFactorRipple1(double length, double width, double height);
    virtual ~FormFactorRipple1();

    FormFactorRipple1 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const final;

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }

    virtual double getRadialExtension() const final;

    virtual complex_t evaluate_for_q(const cvector_t q) const final;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double u) const;

    double m_width;
    double m_height;
    double m_length;

    mutable complex_t m_ay;
    mutable complex_t m_az;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorRipple1>> mP_integrator;
#endif
};

#endif // FORMFACTORRIPPLE1_H
