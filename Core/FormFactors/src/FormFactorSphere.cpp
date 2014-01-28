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
       & FormFactorSphere::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorSphere>(p_mf, this);
}

void FormFactorSphere::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}

FormFactorSphere *FormFactorSphere::clone() const
{
    FormFactorSphere *result = new FormFactorSphere(m_radius, m_height);
    result->setName(getName());
    return result;
}


//! Integrand for complex formfactor.

complex_t FormFactorSphere::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    double Rz = std::sqrt(std::abs(m_radius*m_radius-Z*Z) );
    complex_t q_p = m_q.magxy(); // sqrt(x*x + y*y)
    return Rz*Rz*MathFunctions::Bessel_C1(q_p*Rz) *
        std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
}

//! Complex formfactor.

complex_t FormFactorSphere::evaluate_for_q(const cvector_t& q) const
{   m_q = q;
    if ( std::abs(m_q.mag()) < Numeric::double_epsilon) {
        double HdivR = m_height/m_radius;
        return M_PI/3.*m_radius*m_radius*m_radius
                *(3.*HdivR -1. - (HdivR - 1.)*(HdivR - 1.)*(HdivR - 1.));
    }
    else {
    complex_t iqzR = complex_t(0.0, 1.0)*m_q.z()*(m_height-m_radius);
    complex_t integral = m_integrator->integrate(m_radius-m_height, m_radius);
    return 2*M_PI*integral*std::exp(iqzR);
    }
}


