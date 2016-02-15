// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPrism6.h
//! @brief     Defines class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM6_H
#define FORMFACTORPRISM6_H
#include "IFormFactorBorn.h"

//! @class FormFactorPrism6
//! @ingroup formfactors
//! @brief The formfactor of a prism based on a regular hexagonal.

class BA_CORE_API_ FormFactorPrism6 : public IFormFactorBorn
{
public:
    //! @brief Prism6 constructor
    //! @param radius of hexagonal base (different from R in IsGisaxs)
    //! @param height of Prism6
    FormFactorPrism6(double radius, double height);

    virtual FormFactorPrism6 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;

    virtual double getRadius() const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_height;
    double m_radius;
    complex_t ff_term(
        complex_t qRx, complex_t qRy, double xi, double yi, double xf, double yf ) const;
};

inline double FormFactorPrism6::getHeight() const
{
    return m_height;
}

inline double FormFactorPrism6::getRadius() const
{
    return m_radius;
}

#endif // FORMFACTORPRISM6_H
