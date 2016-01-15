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

#include "FormFactorRipple1.h"
#include "BornAgainNamespace.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"

#include <cmath>

using namespace  BornAgain;

FormFactorRipple1::FormFactorRipple1(double length, double width, double height)
    : m_width(width)
    , m_height(height)
    , m_length(length)
{
    setName(FFRipple1Type);
    check_initialization();
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorRipple1>::mem_function p_mf =
       & FormFactorRipple1::Integrand;
    m_integrator =
        new MemberComplexFunctionIntegrator<FormFactorRipple1>(p_mf, this);
}

FormFactorRipple1::~FormFactorRipple1()
{
    delete m_integrator;
}

bool FormFactorRipple1::check_initialization() const
{
    bool result(true);
    if(m_height <=0.0 || m_width<=0.0 || m_length<=0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorRipple1() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorRipple1::init_parameters()
{
    clearParameterPool();
    registerParameter(Width, &m_width, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Length, &m_length, AttLimits::n_positive());
}

FormFactorRipple1 *FormFactorRipple1::clone() const
{
    return new FormFactorRipple1(m_length, m_width, m_height);
}

void FormFactorRipple1::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

//! Integrand for complex formfactor.
complex_t FormFactorRipple1::Integrand(double Z, void* params) const
{
    (void)params;  // to avoid unused-variable warning
    complex_t iqZ = complex_t(0.0, 1.0)*m_q.z()*Z;
    complex_t aa = std::acos(2.0*Z/m_height - 1.0);
    return std::exp(iqZ)*aa*MathFunctions::Sinc(aa*m_q.y()*m_width/(Units::PI2));
}

//! Complex formfactor.
complex_t FormFactorRipple1::evaluate_for_q(const cvector_t& q) const
{
    m_q = q;
    complex_t factor = m_length*MathFunctions::Sinc(m_q.x()*m_length*0.5)*m_width/Units::PI;
    complex_t aaa = m_q.y()*m_width/(Units::PI2);
    complex_t aaa2 = aaa*aaa;

    // analytical expressions for some particular cases
    if (0.0==m_q.y() && 0.0==m_q.z())
        return factor*Units::PID2*m_height;
    else if (0.0==m_q.z() && 1.0 == aaa2)
        return factor*Units::PID4*m_height;
    else if (0.0==m_q.z())
        return factor*Units::PID2*m_height*MathFunctions::Sinc(m_q.y()*m_width*0.5)/(1.0-aaa2);

    // numerical integration otherwise
    complex_t integral = m_integrator->integrate(0, m_height);
    return factor*integral;
}
