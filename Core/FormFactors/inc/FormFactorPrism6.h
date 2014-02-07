// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPrism6.h
//! @brief     Defines class FormFactorPrism6.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
    ~FormFactorPrism6() {}
    virtual FormFactorPrism6 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getRadius() const { return m_radius; }
    virtual void setRadius(double radius) { m_radius = radius; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:  
    virtual void init_parameters();

private:
    double m_height;
    double m_radius;
    double m_root3; // Cached value of square root of 3
};

#endif // FORMFACTORPRISM6_H


