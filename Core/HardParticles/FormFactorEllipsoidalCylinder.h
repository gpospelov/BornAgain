// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorEllipsoidalCylinder.h
//! @brief     Declares class FormFactorEllipsoidalCylinder
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

#include "IFormFactorBorn.h" // inheriting from

//! @class FormFactorEllipsoidalCylinder
//! @ingroup formfactors
//! @brief The formfactor of an ellipsoidal cylinder.

class BA_CORE_API_ FormFactorEllipsoidalCylinder : public IFormFactorBorn
{
public:
    //! @brief Ellipsoidal Cylinder constructor
    //! @param radius_x half length of one horizontal main axes
    //! @param radius_y half length of the other horizontal main axes
    //! @param height of Ellipsoidal Cylinder
    FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height);

    virtual FormFactorEllipsoidalCylinder* clone() const;

    virtual void accept(ISampleVisitor* visitor) const;

    double getRadiusX() const { return m_radius_x; }
    double getRadiusY() const { return m_radius_y; }
    double getHeight() const { return m_height; }

    virtual double getRadius() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_radius_x;
    double m_radius_y;
    double m_height;
};

#endif // FORMFACTORELLIPSOIDALCYLINDER_H
