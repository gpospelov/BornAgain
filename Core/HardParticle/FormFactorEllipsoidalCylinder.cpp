// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorEllipsoidalCylinder.cpp
//! @brief     Implements class FormFactorEllipsoidalCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorEllipsoidalCylinder.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "Pi.h"

FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(
    double radius_x, double radius_y, double height)
    : m_radius_x(radius_x), m_radius_y(radius_y), m_height(height)
{
    setName(BornAgain::FFEllipsoidalCylinderType);
    registerNonnegativeLength(BornAgain::RadiusX, &m_radius_x);
    registerNonnegativeLength(BornAgain::RadiusY, & m_radius_y);
    registerNonnegativeLength(BornAgain::Height, &m_height);
}

double FormFactorEllipsoidalCylinder::getRadialExtension() const
{
    return ( m_radius_x + m_radius_y ) / 2.0;
}

complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(const cvector_t q) const
{
    complex_t qxRa = q.x()*m_radius_x;
    complex_t qyRb = q.y()*m_radius_y;
    complex_t qzHdiv2 = m_height/2*q.z();

    complex_t Fz = exp_I(qzHdiv2) * MathFunctions::sinc(qzHdiv2);
    complex_t gamma  = std::sqrt((qxRa)*(qxRa) + (qyRb)*(qyRb));
    complex_t J1_gamma_div_gamma = MathFunctions::Bessel_J1c(gamma);

    return Pi::PI2 *m_radius_x*m_radius_y*m_height * Fz*J1_gamma_div_gamma;
}
