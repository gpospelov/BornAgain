// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCone.cpp
//! @brief     Implements class FormFactorCone.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCone.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Units.h"
#include "Exceptions.h"
#include <iostream>
#include "MemberFunctionIntegrator.h"

FormFactorCone::FormFactorCone(double radius,double height,double alpha)
{
    setName("FormFactorCone");
    m_radius = radius;
    m_height = height;
    m_alpha = alpha;
    init_parameters();
}

void FormFactorCone::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
    registerParameter("alpha", & m_alpha);
}

FormFactorCone* FormFactorCone::clone() const
{
   FormFactorCone* ffCone = new FormFactorCone(m_radius, m_height, m_alpha);
   return ffCone;
}

//! Real part of the integral.

double FormFactorCone::evaluate_for_q_real() const
{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorCone>::mem_function p_mf =
       & FormFactorCone::ConeIntegralReal;
    MemberFunctionIntegrator<FormFactorCone> integrator(p_mf,this);
    return integrator.integrate(0, H, (void *)0);
}

//! Integrand for real part of the integral.

double FormFactorCone::ConeIntegralReal(double Z, void* params) const
{
    (void)params;
    complex_t qz = m_q.z();
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();
    double R = m_radius;
    double tan_alpha = std::tan(m_alpha);
    double Rz  = R-(Z/tan_alpha);
    double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
    double J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ?
        MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz :
        0.5;
    double exp_real = std::exp(complex_t(0.0, 1.0)*qz*Z).real();
    return 2*M_PI *Rz*Rz * J1_qrRz_div_qrRz * exp_real;
}

//! Imaginary part of the integral.

double FormFactorCone::evaluate_for_q_imag() const
{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorCone>::mem_function p_mf =
       & FormFactorCone::ConeIntegralImaginary;
    MemberFunctionIntegrator<FormFactorCone> integrator(p_mf,this);
    return integrator.integrate(0, H, (void *)0);
}

//! Integrand for imaginary part of the integral.

double FormFactorCone::ConeIntegralImaginary(double Z, void* params) const
{
    (void)params;
    complex_t qz = m_q.z();
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();
    double R = m_radius;
    double tan_alpha = std::tan(m_alpha);
    double Rz  = R-(Z/tan_alpha);
    double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
    double J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ?
        MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz :
        0.5;
    double exp_imag = std::exp(complex_t(0.0, 1.0)*qz*Z).imag();
    return 2*M_PI *Rz*Rz * J1_qrRz_div_qrRz * exp_imag;
}

//! Complex integral computed as sum of real and imaginary part.

complex_t FormFactorCone::evaluate_for_q(const cvector_t& q) const
{
     m_q = q;
     return complex_t(evaluate_for_q_real(), evaluate_for_q_imag());
}


