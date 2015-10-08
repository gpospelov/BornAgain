// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorRipple1.cpp
//! @brief     Implements class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorInfLongRipple1.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

FormFactorInfLongRipple1::FormFactorInfLongRipple1(double width, double height)
    : m_width(width)
    , m_height(height)
{
    setName("FormFactorInfLongRipple1");
    check_initialization();
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorInfLongRipple1>::mem_function p_mf =
       & FormFactorInfLongRipple1::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorInfLongRipple1>(p_mf, this);
}

bool FormFactorInfLongRipple1::check_initialization() const
{
    bool result(true);
    if(m_height <=0.0 || m_width<=0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorInfLongRipple1() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorInfLongRipple1::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_width, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
}

FormFactorInfLongRipple1 *FormFactorInfLongRipple1::clone() const
{
    FormFactorInfLongRipple1 *result = new FormFactorInfLongRipple1(m_width, m_height);
    result->setName(getName());
    return result;
}


//! Integrand for complex formfactor.

complex_t FormFactorInfLongRipple1::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    complex_t iqZ = complex_t(0.0, 1.0)*m_q.z()*Z;
    complex_t aa = std::acos(2.0*Z/m_height - 1.0);
    return std::exp(iqZ)*aa*MathFunctions::Sinc(aa*m_q.y()*m_width/(Units::PI2));
}

//! Complex formfactor.

complex_t FormFactorInfLongRipple1::evaluate_for_q(const cvector_t& q) const
{
    (const cvector_t) q;  // to avoid unused-variable warning
    throw NotImplementedException(
        "FormFactorInfLongRipple1::evaluate_for_q(q) -> Error: not implemented exception.");
}

complex_t FormFactorInfLongRipple1::evaluate(const WavevectorInfo& wavevectors) const
{
    double qxmin = (wavevectors.getKi() - wavevectors.getKfBin().m_q_upper).x().real();
    double qxmax = (wavevectors.getKi() - wavevectors.getKfBin().m_q_lower).x().real();

    if (qxmin < 0.0 && qxmax < 0.0)
        return 0;

    if (qxmin > 0.0 && qxmax > 0.0)
        return 0;

    cvector_t q = wavevectors.getMiddleQ();

    complex_t integral = m_integrator->integrate(0, m_height);

    return 2.0*m_width*integral;
}

double FormFactorInfLongRipple1::getVolume() const {
    // volume of the infinite object is infinite
    throw NotImplementedException(
                "FormFactorInfLongRipple1::getVolume() -> Error: not implemented exception. Volume of the infinite object is infinite.");
}
