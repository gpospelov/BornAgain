// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorRipple2.cpp
//! @brief     Implements class FormFactorRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorRipple2.h"
#include "BornAgainNamespace.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

#include <cmath>

using namespace  BornAgain;

FormFactorRipple2::FormFactorRipple2(double length, double width, double height, double asymetry)
    : m_width(width)
    , m_height(height)
    , m_length(length)
    , m_d(asymetry)
{
    setName(FFRipple2Type);
    check_initialization();
    init_parameters();
}

bool FormFactorRipple2::check_initialization() const
{
    bool result(true);
    std::string message;
    if(-1*m_width > 2.*m_d) {
        result = false;
        message = std::string("Check for '-1*width <= 2.*asymmetry' failed.");
    }
    if(m_width < 2.*m_d) {
        result = false;
        message = std::string("Check for 'width >= 2.*asymmetry' failed.");
    }
    if(m_height <=0) {
        result = false;
        message = std::string("Check for 'height > 0' failed.");
    }

    if(!result) {
        std::ostringstream ostr;
        ostr << "FormFactorRipple2() -> Error in class initialization with parameters ";
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " length:" << m_length;
        ostr << " asymmetry:" << m_d << "\n\n";
        ostr << message;
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorRipple2::init_parameters()
{
    clearParameterPool();
    registerParameter(Width, &m_width, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Length, &m_length, AttLimits::n_positive());
    registerParameter(AsymmetryLength, &m_d);
}

FormFactorRipple2 *FormFactorRipple2::clone() const
{
    return new FormFactorRipple2(m_length, m_width, m_height, m_d);
}

void FormFactorRipple2::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorRipple2::getRadius() const
{
    return ( m_width + m_length ) / 4.0;
}

//! Complex formfactor.
complex_t FormFactorRipple2::evaluate_for_q(const cvector_t &q) const
{
    m_q = q;
    complex_t factor = m_length * MathFunctions::sinc(m_q.x() * m_length * 0.5) * m_width;
    complex_t result = 0;
    complex_t iqzH = complex_t(0.0, 1.0) * m_q.z() * m_height;
    complex_t iqyW = complex_t(0.0, 1.0) * m_q.y() * m_width;
    complex_t aaa = 2.0 * (m_d * m_q.y() + m_height * m_q.z());

    if (0.0 == m_q.y() && 0.0 == m_q.z())
        result = m_height * 0.5;
    else if (0.0 == m_q.y())
        result = (1.0 - std::exp(iqzH) + iqzH) / (m_height * m_q.z() * m_q.z());
    else if (1.0 == aaa / (m_q.y() * m_width))
        result = m_height * std::exp(iqzH) * (1.0 - std::exp(-1.0 * iqyW) - iqyW)
                 / (m_q.y() * m_q.y() * m_width * m_width);
    else if (-1.0 == aaa / (m_q.y() * m_width))
        result = m_height * std::exp(iqzH) * (1.0 - std::exp(-1.0 * iqyW) + iqyW)
                 / (m_q.y() * m_q.y() * m_width * m_width);
    else {
        complex_t iHqzdqy = complex_t(0.0, 1.0) * (m_q.z() * m_height + m_q.y() * m_d);
        complex_t Hqzdqy = m_q.z() * m_height + m_q.y() * m_d;
        result = std::cos(m_q.y() * m_width * 0.5)
                 + 2.0 * iHqzdqy * std::sin(m_q.y() * m_width * 0.5) / (m_width * m_q.y());
        result = result * std::exp(-1.0 * iHqzdqy) - 1.0;
        result = result * 4.0 * m_height * std::exp(iqzH)
                 / (4.0 * Hqzdqy * Hqzdqy - m_q.y() * m_q.y() * m_width * m_width);
    }
    return factor * result;
}
