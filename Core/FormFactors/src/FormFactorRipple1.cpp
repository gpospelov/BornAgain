// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorRipple1.cpp
//! @brief     Implements class FormFactorRipple1.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorRipple1.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorRipple1::FormFactorRipple1(double width, double height, double length)
    : m_width(width)
    , m_height(height)
    , m_length(length)
{
    setName("FormFactorRipple1");
    assert(m_height > 0);
    assert(m_width > 0);
    assert(m_length > 0);
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorRipple1>::mem_function p_mf =
       & FormFactorRipple1::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorRipple1>(p_mf, this);
}

void FormFactorRipple1::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_width);
    registerParameter("height", &m_height);
    registerParameter("length", &m_length);
}

FormFactorRipple1 *FormFactorRipple1::clone() const
{
    FormFactorRipple1 *result = new FormFactorRipple1(m_width, m_height, m_length);
    result->setName(getName());
    return result;
}


//! Integrand for complex formfactor.

complex_t FormFactorRipple1::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    complex_t iqZ = complex_t(0.0, 1.0)*m_q.z()*Z;
    complex_t aa = std::acos(2.0*Z/m_height - 1.0);
    return std::exp(iqZ)*aa*MathFunctions::Sinc(aa*m_q.y()*m_width/(2*M_PI));
}

//! Complex formfactor.

complex_t FormFactorRipple1::evaluate_for_q(const cvector_t& q) const
{   
	m_q = q;
    complex_t factor = m_length*MathFunctions::Sinc(m_q.x()*m_length*0.5)*m_width/M_PI;
    complex_t aaa = m_q.y()*m_width/(2*M_PI);
    complex_t aaa2 = aaa*aaa;

    // analytical expressions for some particular cases
    if (0.0==m_q.y() && 0.0==m_q.z())
        return factor*M_PI_2*m_height;
    else if (0.0==m_q.z() && 1.0 == aaa2)
        return factor*M_PI_4*m_height;
    else if (0.0==m_q.z())
        return factor*M_PI_2*m_height*MathFunctions::Sinc(m_q.y()*m_width*0.5)/(1.0-aaa2);

    // numerical integration otherwise
    complex_t integral = m_integrator->integrate(0, m_height);
    return factor*integral;
}


