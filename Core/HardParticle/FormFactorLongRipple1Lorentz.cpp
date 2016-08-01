// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongRipple1Lorentz.cpp
//! @brief     Implements class FormFactorLongRipple1Lorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLongRipple1Lorentz.h"
#include "AttLimits.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathFunctions.h"
#include "Units.h"

using namespace BornAgain;

FormFactorLongRipple1Lorentz::FormFactorLongRipple1Lorentz(
    double length, double width, double height)
    : m_width(width)
    , m_height(height)
    , m_length(length)
{
    setName(FFLongRipple1LorentzType);
    check_initialization();
    init_parameters();

    mP_integrator = make_integrator_complex(this, &FormFactorLongRipple1Lorentz::Integrand);
}

FormFactorLongRipple1Lorentz::~FormFactorLongRipple1Lorentz() {}

bool FormFactorLongRipple1Lorentz::check_initialization() const
{
    bool result(true);
    if(m_height <=0.0 || m_width<=0.0 || m_length<=0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorLongRipple1Lorentz() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorLongRipple1Lorentz::init_parameters()
{
    registerParameter(Width, &m_width, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Length, &m_length, AttLimits::n_positive());
}

FormFactorLongRipple1Lorentz* FormFactorLongRipple1Lorentz::clone() const
{
    return new FormFactorLongRipple1Lorentz(m_length, m_width, m_height);
}

void FormFactorLongRipple1Lorentz::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

double FormFactorLongRipple1Lorentz::getRadialExtension() const
{
    return ( m_width + m_length ) / 4.0;
}

//! Integrand for complex formfactor.
complex_t FormFactorLongRipple1Lorentz::Integrand(double Z) const
{
    complex_t aa = std::acos(2.0*Z/m_height - 1.0);
    return exp_I(m_q.z()*Z) * aa * MathFunctions::sinc(aa*m_q.y() * m_width/(Units::PI2));
}

//! Complex formfactor.
complex_t FormFactorLongRipple1Lorentz::evaluate_for_q(const cvector_t q) const
{
    m_q = q;

    complex_t qxL2 = 2.5*std::pow(m_length * q.x(), 2);
    complex_t factor = m_length/(1.0 + qxL2)*m_width/Units::PI;

    complex_t aaa = q.y()*m_width/(Units::PI2);
    complex_t aaa2 = aaa*aaa;

    // analytical expressions for some particular cases
    if (0.0==q.y() && 0.0==q.z())
        return factor*Units::PID2*m_height;
    else if (0.0==q.z() && 1.0 == aaa2)
        return factor*Units::PID4*m_height;
    else if (0.0==q.z())
        return factor*Units::PID2*m_height*MathFunctions::sinc(q.y()*m_width*0.5)/(1.0-aaa2);

    // numerical integration otherwise
    complex_t integral = mP_integrator->integrate(0, m_height);
    return factor*integral;
}
