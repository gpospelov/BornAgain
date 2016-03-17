// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTruncatedSphere.h
//! @brief     Defines class FormFactorTruncatedSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDSPHERE_H
#define FORMFACTORTRUNCATEDSPHERE_H

#include "IFormFactorBorn.h"

#include <memory>

// Forward declaration to prevent IntegratorComplex.h to be parsed for Python API:
template <class T> class IntegratorComplex;

//! @class FormFactorTruncatedSphere
//! @ingroup formfactors
//! @brief The formfactor of a truncated Sphere.

class BA_CORE_API_ FormFactorTruncatedSphere : public IFormFactorBorn
{
public:
    //! @brief TruncatedSphere constructor
    //! @param radius of Truncated Sphere
    //! @param height of Truncated Sphere
    FormFactorTruncatedSphere(double radius, double height);

    virtual ~FormFactorTruncatedSphere();

    virtual FormFactorTruncatedSphere *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    double getHeight() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();
    virtual complex_t evaluate_for_q(const cvector_t& q) const;

private:
    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

#ifndef GCCXML_SKIP_THIS
    std::unique_ptr<IntegratorComplex<FormFactorTruncatedSphere>> mP_integrator;
#endif
};

inline double FormFactorTruncatedSphere::getRadius() const
{
    return m_radius;
}

inline double FormFactorTruncatedSphere::getHeight() const
{
    return m_height;
}

#endif // FORMFACTORTRUNCATEDSPHERE_H


