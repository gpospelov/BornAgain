// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorRipple2.cpp
//! @brief     Implements class FormFactorRipple2.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorRipple2.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorRipple2::FormFactorRipple2(double width, double height, double length, double asymetry)
    : m_width(width)
    , m_height(height)
    , m_length(length)
    , m_d(asymetry)
{
    setName("FormFactorRipple2");
    assert(-1*m_width <= 2.*m_d);
    assert(m_width >= 2.*m_d);
    assert(m_height > 0);
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorRipple2>::mem_function p_mf =
       & FormFactorRipple2::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorRipple2>(p_mf, this);
}

void FormFactorRipple2::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_width);
    registerParameter("height", &m_height);
    registerParameter("length", &m_length);
    registerParameter("asymetry", &m_d);
}

FormFactorRipple2 *FormFactorRipple2::clone() const
{
    FormFactorRipple2 *result = new FormFactorRipple2(m_width, m_height, m_length, m_d);
    result->setName(getName());
    return result;
}


//! Integrand for complex formfactor.

complex_t FormFactorRipple2::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    complex_t p1 = (1.0-Z/m_height)*MathFunctions::Sinc(m_q.y()*m_width*0.5*(1.0-Z/m_height));
    return p1*std::exp(complex_t(0.0, 1.0)*(-1.0*m_q.y()*m_d*(1-Z/m_height) + m_q.z()*Z));
}

//! Complex formfactor.

complex_t FormFactorRipple2::evaluate_for_q(const cvector_t& q) const
{   
	m_q = q;
    complex_t factor = m_length*MathFunctions::Sinc(m_q.x()*m_length*0.5)*m_width;
    complex_t integral = m_integrator->integrate(0, m_height);
    return factor*integral;
}


