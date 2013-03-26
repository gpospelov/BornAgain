// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorSphere.cpp
//! @brief     Implements class FormFactorSphere.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorSphere.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorSphere::FormFactorSphere(double radius, double height)
    : m_radius(radius)
    , m_height(height)
{
    setName("FormFactorSphere");
    assert(m_height <= 2.*m_radius);
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorSphere>::mem_function p_mf =
        &FormFactorSphere::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorSphere>(p_mf, this);
}

void FormFactorSphere::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("radius", &m_radius);
    getParameterPool()->registerParameter("height", &m_height);
}

//! Integrand for complex formfactor.

complex_t FormFactorSphere::Integrand(double Z, void* params) const
{
    (void)params;
    double Rz = std::sqrt( std::abs(m_radius*m_radius-Z*Z) );
    complex_t q_p = m_q.magxy(); // sqrt(x*x + y*y)
    return Rz*Rz*MathFunctions::Bessel_C1(std::abs(q_p*Rz)) *
        std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
}

//! Complex formfactor.

complex_t FormFactorSphere::evaluate_for_q(const cvector_t &q) const
{
    m_q = q;
    complex_t iqzR = complex_t(0.0, 1.0)*m_q.z()*(m_height-m_radius);
    complex_t integral = m_integrator->integrate(m_radius-m_height, m_radius);
    return 2*M_PI*integral*std::exp(iqzR);
}
