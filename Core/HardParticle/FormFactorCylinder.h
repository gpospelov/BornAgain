// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCylinder.h
//! @brief     Declares class FormFactorCylinder.
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

#include "IFormFactorBorn.h" // inheriting from

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
    virtual ~FormFactorCylinder() {}

    FormFactorCylinder *clone() const { return new FormFactorCylinder(m_radius, m_height); }
    void accept(ISampleVisitor *visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadius() const { return m_radius; }

    double getRadialExtension() const final { return m_radius; }

    complex_t evaluate_for_q(const cvector_t q) const final;

private:
    double m_radius;
    double m_height;
};

#endif // FORMFACTORCYLINDER_H
