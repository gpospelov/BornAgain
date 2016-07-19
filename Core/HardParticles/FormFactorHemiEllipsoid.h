// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorHemiEllipsoid.h
//! @brief     Declares class FormFactorHemiEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORHEMIELLIPSOID_H
#define FORMFACTORHEMIELLIPSOID_H

#include "IFormFactorBorn.h"
#include "IntegratorComplex.h"

//! @class FormFactorHemiEllipsoid
//! @ingroup formfactors
//! @brief The formfactor of an hemi ellipsoid.

class BA_CORE_API_ FormFactorHemiEllipsoid : public IFormFactorBorn
{
public:
    //! @brief Hemi Ellipsoid constructor
    //! @param radius_x half length of one horizontal main axes
    //! @param radius_y half length of the other horizontal main axes
    //! @param height of Hemi Ellipsoid
    FormFactorHemiEllipsoid(double radius_x, double radius_y, double height);

    virtual ~FormFactorHemiEllipsoid();

    virtual FormFactorHemiEllipsoid* clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const { return m_height; }
    double getRadiusX() const { return m_radius_x; }
    double getRadiusY() const { return m_radius_y; }
    virtual double getRadius() const;

    virtual complex_t evaluate_for_q (const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double Z) const;

    double m_radius_x;
    double m_radius_y;
    double m_height;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorHemiEllipsoid>> mP_integrator;
#endif
};

#endif // FORMFACTORHEMIELLIPSOID_H
