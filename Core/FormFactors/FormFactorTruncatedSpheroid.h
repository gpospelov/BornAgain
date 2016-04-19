// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorTruncatedSpheroid.h
//! @brief     Defines class FormFactorTruncatedSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDSPHEROID_H
#define FORMFACTORTRUNCATEDSPHEROID_H

#include "IFormFactorBorn.h"

#include <memory>

// Forward declaration to prevent IntegratorComplex.h to be parsed for Python API:
template <class T> class IntegratorComplex;

//! @class FormFactorTruncatedSpheroid
//! @ingroup formfactors
//! @brief The formfactor of a truncated spheroid.

class BA_CORE_API_ FormFactorTruncatedSpheroid : public IFormFactorBorn
{
public:
    //! @brief TruncatedSpheroid constructor
    //! @param radius of Truncated Spheroid
    //! @param height of Truncated Spheroid
    //! @param flattening parameter in vertical direction (full height: 2 x flattening x radius)

    FormFactorTruncatedSpheroid(double radius, double height, double height_flattening);

    virtual ~FormFactorTruncatedSpheroid();

    virtual FormFactorTruncatedSpheroid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;

    double getHeightFlattening() const;

    virtual double getRadius() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:

    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    double m_height_flattening;
    mutable cvector_t m_q;

#ifndef GCCXML_SKIP_THIS
    std::unique_ptr<IntegratorComplex<FormFactorTruncatedSpheroid>> mP_integrator;
#endif
};

inline double FormFactorTruncatedSpheroid::getHeight() const
{
    return m_height;
}

inline double FormFactorTruncatedSpheroid::getHeightFlattening() const
{
    return m_height_flattening;
}

inline double FormFactorTruncatedSpheroid::getRadius() const
{
    return m_radius;
}


#endif // FORMFACTORTRUNCATEDSPHEROID_H
