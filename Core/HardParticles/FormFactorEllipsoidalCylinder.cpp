// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorEllipsoidalCylinder.cpp
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
#include "Units.h"

using namespace BornAgain;

FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y,
                                                             double height)
{
    setName(FFEllipsoidalCylinderType);
    m_height = height;
    m_radius_x = radius_x;
    m_radius_y = radius_y;
    check_initialization();
    init_parameters();
}

FormFactorEllipsoidalCylinder* FormFactorEllipsoidalCylinder::clone() const
{
    return new FormFactorEllipsoidalCylinder(m_radius_x, m_radius_y, m_height);
}

void FormFactorEllipsoidalCylinder::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

double FormFactorEllipsoidalCylinder::getRadius() const
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

    return Units::PI2 *m_radius_x*m_radius_y*m_height * Fz*J1_gamma_div_gamma;
}

bool FormFactorEllipsoidalCylinder::check_initialization() const
{
    return true;
}

void FormFactorEllipsoidalCylinder::init_parameters()
{
    clearParameterPool();
    registerParameter(RadiusX, &m_radius_x, AttLimits::n_positive());
    registerParameter(RadiusY, & m_radius_y, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}
