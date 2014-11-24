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
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorRipple2::FormFactorRipple2(double length, double width, double height, double asymetry)
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
    FormFactorRipple2 *result = new FormFactorRipple2(m_length, m_width, m_height, m_d);
    result->setName(getName());
    return result;
}


//! Complex formfactor.

complex_t FormFactorRipple2::evaluate_for_q(const cvector_t& q) const
{
    m_q = q;
    complex_t factor = m_length*MathFunctions::Sinc(m_q.x()*m_length*0.5)*m_width;
    complex_t result = 0;
    complex_t iqzH = complex_t(0.0, 1.0)*m_q.z()*m_height;
    complex_t iqyW = complex_t(0.0, 1.0)*m_q.y()*m_width;
    complex_t aaa = 2.0*(m_d*m_q.y() + m_height*m_q.z());

    if (0.0==m_q.y() && 0.0==m_q.z())
        result = m_height*0.5;
    else if (0.0==m_q.y())
        result = (1.0 - std::exp(iqzH) + iqzH)/(m_height*m_q.z()*m_q.z());
    else if (1.0 == aaa/(m_q.y()*m_width))
        result = m_height*std::exp(iqzH)*(1.0 - std::exp(-1.0*iqyW) - iqyW)/(m_q.y()*m_q.y()*m_width*m_width);
    else if (-1.0 == aaa/(m_q.y()*m_width))
        result = m_height*std::exp(iqzH)*(1.0 - std::exp(-1.0*iqyW) + iqyW)/(m_q.y()*m_q.y()*m_width*m_width);
    else {
        complex_t iHqzdqy = complex_t(0.0, 1.0)*(m_q.z()*m_height + m_q.y()*m_d);
        complex_t Hqzdqy = m_q.z()*m_height + m_q.y()*m_d;
        result = std::cos(m_q.y()*m_width*0.5) + 2.0*iHqzdqy*std::sin(m_q.y()*m_width*0.5)/(m_width*m_q.y());
        result = result*std::exp(-1.0*iHqzdqy) - 1.0;
        result = result*4.0*m_height*std::exp(iqzH)/(4.0*Hqzdqy*Hqzdqy - m_q.y()*m_q.y()*m_width*m_width);
    }
    return factor*result;
}


