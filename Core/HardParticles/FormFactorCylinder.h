// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorCylinder.h
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
    virtual FormFactorCylinder *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const { return m_height; }

    virtual double getRadius() const { return m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_radius;
    double m_height;
};

#endif // FORMFACTORCYLINDER_H
