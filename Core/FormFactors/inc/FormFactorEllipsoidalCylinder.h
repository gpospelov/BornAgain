// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorEllipsoidalCylinder.h
//! @brief     Defines class FormFactorEllipsoidalCylinder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORELLIPSOIDALCYLINDER_H
#define FORMFACTORELLIPSOIDALCYLINDER_H

#include "IFormFactorBorn.h"

//! @class FormFactorEllipsoidalCylinder
//! @ingroup formfactors
//! @brief The formfactor of an ellipsoidal cylinder.

class BA_CORE_API_ FormFactorEllipsoidalCylinder : public IFormFactorBorn
{
public:
    //! @brief Ellipsoidal Cylinder constructor
    //! @param radius_a half length of one horizontal main axes
    //! @param radius_b half length of the other horizontal main axes
    //! @param height of Ellipsoidal Cylinder
    FormFactorEllipsoidalCylinder(double radius_a, double radius_b,
                        double height);
    ~FormFactorEllipsoidalCylinder() {}
    virtual FormFactorEllipsoidalCylinder *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    double getRadiusA() const { return m_radius_a; }
    virtual void setRadiusA(double radius_a) { m_radius_a = radius_a; }

    virtual double getRadiusB() const { return m_radius_b; }
    virtual void setRadiusB(double radius_b) { m_radius_b = radius_b; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:

    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_radius_a;
    double m_radius_b;
    double m_height;

};

#endif // FORMFACTORELLIPSOIDALCYLINDER_H


