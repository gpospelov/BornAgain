// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorEllipsoidalCylinder.cpp
//! @brief     Implements class FormFactorEllipsoidalCylinder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorEllipsoidalCylinder.h"
#include "MathFunctions.h"

FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_a,
                                                             double radius_b,
                                                             double height)
{
    setName("FormFactorEllipsoidalCylinder");
    m_height = height;
    m_radius_a = radius_a;
    m_radius_b  = radius_b;
    init_parameters();
}

FormFactorEllipsoidalCylinder* FormFactorEllipsoidalCylinder::clone() const
{
    return new FormFactorEllipsoidalCylinder(m_radius_a, m_radius_b, m_height);
}

complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxRa = q.x()*m_radius_a;
    complex_t qyRb = q.y()*m_radius_b;
    complex_t qzHdiv2 = q.z()*m_height/2.0;

    complex_t Fz = std::exp(complex_t(0.0, 1.0)*qzHdiv2)
                   *MathFunctions::Sinc(qzHdiv2);
    complex_t gamma  = std::sqrt((qxRa)*(qxRa) + (qyRb)*(qyRb));
    complex_t J1_gamma_div_gamma = MathFunctions::Bessel_C1(gamma);

    return 2.*M_PI *m_radius_a*m_radius_b*m_height * Fz*J1_gamma_div_gamma;

}

void FormFactorEllipsoidalCylinder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius_a", &m_radius_a);
    registerParameter("radius_b", & m_radius_b);
    registerParameter("height", &m_height);
}


