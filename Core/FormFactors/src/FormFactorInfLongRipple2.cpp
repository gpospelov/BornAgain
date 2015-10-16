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

#include "FormFactorInfLongRipple2.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorInfLongRipple2::FormFactorInfLongRipple2(double width, double height, double asymetry)
    : m_width(width)
    , m_height(height)
    , m_d(asymetry)
{
    setName("FormFactorInfLongRipple2");
    check_initialization();
    init_parameters();
}

bool FormFactorInfLongRipple2::check_initialization() const
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
        ostr << "FormFactorInfLongRipple2() -> Error in class initialization with parameters ";
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " asymmetry:" << m_d << "\n\n";
        ostr << message;
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorInfLongRipple2::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_width, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
    registerParameter("asymetry", &m_d, AttLimits::n_positive());
}

FormFactorInfLongRipple2 *FormFactorInfLongRipple2::clone() const
{
    FormFactorInfLongRipple2 *result = new FormFactorInfLongRipple2(m_width, m_height, m_d);
    result->setName(getName());
    return result;
}

double FormFactorInfLongRipple2::getVolume() const {
    // volume of the infinite object is infinite
    throw NotImplementedException(
                "FormFactorInfLongRipple2::getVolume() -> Error: not implemented exception. Volume of the infinite object is infinite.");
}

//! Complex formfactor.

complex_t FormFactorInfLongRipple2::evaluate_for_q(const cvector_t& q) const
{
    (const cvector_t) q;  // to avoid unused-variable warning
    throw NotImplementedException(
        "FormFactorInfLongRipple2::evaluate_for_q(q) -> Error: not implemented exception.");
}

complex_t FormFactorInfLongRipple2::evaluate(const WavevectorInfo& wavevectors) const
{
    double qxmin = wavevectors.getQ().x().real();
    double qxmax = wavevectors.getQ().x().real();

    if (qxmin < 0.0 && qxmax < 0.0)
        return 0;

    if (qxmin > 0.0 && qxmax > 0.0)
        return 0;

    cvector_t q = wavevectors.getQ();

    complex_t factor = Units::PI2*m_width;
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


