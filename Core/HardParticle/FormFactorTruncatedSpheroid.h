// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSpheroid.h
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
#include "IntegratorComplex.h"

//! @brief   A spheroid, i.e. an ellipsoid with two equal axis, truncated by a plane perpendicular
//!            to the third axis.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorTruncatedSpheroid : public IFormFactorBorn
{
public:
    FormFactorTruncatedSpheroid(double radius, double height, double height_flattening);
    virtual ~FormFactorTruncatedSpheroid() {}

    FormFactorTruncatedSpheroid* clone() const {
        return new FormFactorTruncatedSpheroid(m_radius, m_height, m_height_flattening); }
    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    double getRadius() const { return m_radius; }
    double getHeight() const { return m_height; }
    double getHeightFlattening() const { return m_height_flattening; }

    double getRadialExtension() const final { return m_radius; }

    complex_t evaluate_for_q(const cvector_t q) const final;

protected:
    virtual bool check_initialization() const;

private:

    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    double m_height_flattening;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorTruncatedSpheroid>> mP_integrator;
#endif
};

#endif // FORMFACTORTRUNCATEDSPHEROID_H
