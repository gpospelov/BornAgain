// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSpheroid.cpp
//! @brief     Implements class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSpheroid.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Pi.h"

FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height )
    : m_radius(radius), m_height(height)
{
    setName(BornAgain::FFFullSpheroidType);
    registerNonnegativeLength(BornAgain::Radius, &m_radius);
    registerNonnegativeLength(BornAgain::Height, &m_height);
    mP_integrator = make_integrator_complex(this, &FormFactorFullSpheroid::Integrand);
}

//! Integrand for complex formfactor.
complex_t FormFactorFullSpheroid::Integrand(double Z) const
{
    double R = m_radius;
    double H = m_height;

    double Rz  = R*std::sqrt(1-4.0*Z*Z/(H*H));
    complex_t qxy = std::sqrt(m_q.x()*m_q.x()+m_q.y()*m_q.y());
    complex_t qrRz = qxy*Rz;
    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_J1c(qrRz);

    return Rz*Rz* J1_qrRz_div_qrRz *std::cos(m_q.z()*Z);
}

complex_t FormFactorFullSpheroid::evaluate_for_q(const cvector_t q) const
{
    double H = m_height;
    double R = m_radius;
    m_q = q;

    if (std::abs(m_q.mag()) <= Numeric::double_epsilon) {
        return Pi::PI2*R*R*H/3.;
    } else {
        complex_t qzH_half = H/2*q.z();
        return 4 * Pi::PI * mP_integrator->integrate(0.0, H/2.0) * exp_I(qzH_half);
    }
}
