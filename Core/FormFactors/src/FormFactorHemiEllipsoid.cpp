// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorHemiEllipsoid.cpp
//! @brief     Implements class FormFactorHemiEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorHemiEllipsoid.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

#include <cmath>

using namespace  BornAgain;

FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(
    double radius_a, double radius_b, double height)
{
    setName(FFHemiEllipsoidType);
    m_radius_x = radius_a;
    m_radius_y  = radius_b;
    m_height = height;
    check_initialization();
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorHemiEllipsoid>::mem_function p_mf =
       & FormFactorHemiEllipsoid::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorHemiEllipsoid>(p_mf, this);
}

bool FormFactorHemiEllipsoid::check_initialization() const
{
    return true;
}

void FormFactorHemiEllipsoid::init_parameters()
{
    clearParameterPool();
    registerParameter(RadiusX, &m_radius_x, AttLimits::n_positive());
    registerParameter(RadiusY, & m_radius_y, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}

FormFactorHemiEllipsoid* FormFactorHemiEllipsoid::clone() const
{
   return new FormFactorHemiEllipsoid(m_radius_x,  m_radius_y, m_height);
}

void FormFactorHemiEllipsoid::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorHemiEllipsoid::getRadius() const
{
    return ( m_radius_x + m_radius_y ) / 2.0;
}

//! Integrand for complex formfactor.
complex_t FormFactorHemiEllipsoid::Integrand(double Z, void* params) const
{
    (void)params;
    double R = m_radius_x;
    double W = m_radius_y;
    double H = m_height;

    double Rz = R* std::sqrt(1.0 - Z*Z/(H*H));
    double Wz = W* std::sqrt(1.0 - Z*Z/(H*H));

    complex_t qxRz = m_q.x()*Rz;
    complex_t qyWz = m_q.y()*Wz;

    complex_t gamma = std::sqrt (qxRz*qxRz + qyWz*qyWz);
    complex_t J1_gamma_div_gamma = MathFunctions::Bessel_C1(gamma);
    complex_t exp_imag = std::exp(complex_t(0.0,1.0)*m_q.z()*Z);

    return Rz * Wz * J1_gamma_div_gamma *exp_imag;
}

complex_t FormFactorHemiEllipsoid::evaluate_for_q(const cvector_t& q) const
{
     m_q = q;
     double R = m_radius_x;
     double W = m_radius_y;
     double H = m_height;

     if (std::abs(m_q.mag()) <= Numeric::double_epsilon) {
         return Units::PI2*R*W*H/3.;
     } else {
         return Units::PI2*m_integrator->integrate(0.,H );
     }
}
