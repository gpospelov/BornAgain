// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCone6.h
//! @brief     Defines class FormFactorCone6
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE6_H
#define FORMFACTORCONE6_H

#include "IFormFactorBorn.h"

#include <memory>

// Forward declaration to prevent IntegratorComplex.h to be parsed for Python API:
template <class T> class IntegratorComplex;

//! @class FormFactorCone6
//! @ingroup formfactors
//! @brief The formfactor of a cone6.
class BA_CORE_API_ FormFactorCone6 : public IFormFactorBorn
{
public:
    //! @brief Cone6 constructor
    //! @param radius of hexagonal base (different from R in IsGisaxs)
    //! @param height of Cone6
    //! @param angle in radians between base and facet
    FormFactorCone6(double radius, double height,  double alpha);
    virtual ~FormFactorCone6();

    virtual FormFactorCone6* clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;

    virtual double getRadius() const;

    double getAlpha() const;

    virtual complex_t evaluate_for_q (const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:

    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    double m_alpha;
    double m_root3; // Cached value of square root of 3
    mutable cvector_t m_q;

#ifndef GCCXML_SKIP_THIS
    std::unique_ptr<IntegratorComplex<FormFactorCone6>> mP_integrator;
#endif
};

inline double FormFactorCone6::getHeight() const
{
    return m_height;
}

inline double FormFactorCone6::getRadius() const
{
    return m_radius;
}

inline double FormFactorCone6::getAlpha() const
{
    return m_alpha;
}

#endif // FORMFACTORCONE6_H


