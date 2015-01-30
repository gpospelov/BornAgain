// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCylinder.h
//! @brief     Defines class FormFactorCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCYLINDER_H
#define FORMFACTORCYLINDER_H

#include "IFormFactorBorn.h"

//! @class FormFactorCylinder
//! @ingroup formfactors
//! @brief The formfactor of a cylinder.

class BA_CORE_API_ FormFactorCylinder : public IFormFactorBorn
{
public:
    //! @brief Cylinder constructor
    //! @param radius of Cylinder's base
    //! @param height of Cylinder
    FormFactorCylinder(double radius, double height);
    ~FormFactorCylinder() {}
    virtual FormFactorCylinder *clone() const;

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
    double m_radius;
    double m_height;
};

#endif // FORMFACTORCYLINDER_H


