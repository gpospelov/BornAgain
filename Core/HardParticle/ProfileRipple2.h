// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/ProfileRipple2.h
//! @brief     Defines class ProfileRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PROFILERIPPLE2_H
#define PROFILERIPPLE2_H

#include "Core/Scattering/IFormFactorBorn.h"
#include "Core/Tools/Integrator.h"

//! Base class for form factors with a cosine ripple profile in the yz plane.

class BA_CORE_API_ ProfileRipple2 : public IFormFactorBorn
{
public:
    ProfileRipple2(double length, double width, double height, double asymmetry);

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getAsymmetry() const { return m_asymmetry; }

    double radialExtension() const override final;

    complex_t evaluate_for_q(cvector_t q) const override final
    {
        return factor_x(q.x()) * factor_yz(q.y(), q.z());
    }

protected:
    void onChange() override final;
    virtual complex_t factor_x(complex_t qx) const = 0;

    double m_length;
    double m_width;
    double m_height;
    double m_asymmetry;

private:
    complex_t factor_yz(complex_t qy, complex_t qz) const;
    bool check_initialization() const;
    mutable ComplexIntegrator m_integrator;
};

#endif // PROFILERIPPLE2_H
