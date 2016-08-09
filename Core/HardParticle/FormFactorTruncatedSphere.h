// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSphere.h
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
#include "IntegratorComplex.h"

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

    FormFactorTruncatedSphere *clone() const {
        return new FormFactorTruncatedSphere(m_radius, m_height); }
    void accept(ISampleVisitor *visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadius() const { return m_radius; }

    double getRadialExtension() const final { return m_radius; }

protected:
    virtual bool check_initialization() const;
    virtual complex_t evaluate_for_q(const cvector_t q) const;

private:
    complex_t Integrand(double Z) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

#ifndef SWIG
    std::unique_ptr<IntegratorComplex<FormFactorTruncatedSphere>> mP_integrator;
#endif
};

#endif // FORMFACTORTRUNCATEDSPHERE_H
