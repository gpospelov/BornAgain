// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorCone.h
//! @brief     Defines class FormFactorCone
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE_H
#define FORMFACTORCONE_H

#include "IFormFactorBorn.h"

#include <memory>

// Forward declaration to prevent IntegratorComplex.h to be parsed for Python API:
template <class T> class IntegratorComplex;

//! @class FormFactorCone
//! @ingroup formfactors
//! @brief The formfactor of a cone.
class BA_CORE_API_ FormFactorCone : public IFormFactorBorn
{
public:
    //! @brief Cone constructor
    //! @param radius of Cone's base
    //! @param height of Cone
    //! @param angle in radians between base and facet
    FormFactorCone(double radius, double height,  double alpha);
    virtual ~FormFactorCone();

    virtual FormFactorCone* clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;

    virtual double getRadius() const;

    double getAlpha() const;

    virtual complex_t evaluate_for_q (const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    double m_alpha;
    mutable cvector_t m_q;

#ifndef GCCXML_SKIP_THIS
    std::unique_ptr<IntegratorComplex<FormFactorCone>> mP_integrator;
#endif
};

inline void FormFactorCone::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

inline double FormFactorCone::getHeight() const
{
    return m_height;
}

inline double FormFactorCone::getRadius() const
{
    return m_radius;
}

inline double FormFactorCone::getAlpha() const
{
    return m_alpha;
}

#endif // FORMFACTORCONE_H


