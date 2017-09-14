// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple2.cpp
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
#include "Exceptions.h"
#include "MathFunctions.h"
#include "RealParameter.h"
#include "RippleSawtooth.h"

//! @brief Constructor of a triangular ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
//! @param asymmetry: asymmetry length of the triangular profile in nanometers
FormFactorRipple2::FormFactorRipple2(double length, double width, double height, double asymmetry)
    : m_length(length), m_width(width), m_height(height), m_d(asymmetry)
{
    setName(BornAgain::FFRipple2Type);
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::AsymmetryLength, &m_d).setUnit(BornAgain::UnitsNm);
    onChange();
}

double FormFactorRipple2::radialExtension() const
{
    return ( m_width + m_length ) / 4.0;
}

//! Complex formfactor.
complex_t FormFactorRipple2::evaluate_for_q(cvector_t q) const
{
    complex_t factor = m_length * MathFunctions::sinc(q.x()*m_length/2.) * m_height * m_width;
    complex_t result;
    const complex_t qyW2 = q.y() * m_width * 0.5;
    const complex_t qyd = q.y() * m_d;
    const complex_t qzH = q.z() * m_height;
    const complex_t a = qzH + qyd;
    // dimensionless scale factors
    const double a_scale = std::abs(a);
    const double w_scale = std::abs(qyW2);

    if (w_scale < 1.e-5) { // |q_y*W| << 1
        if (a_scale < 1e-5) { // |q_y*W| << 1 && |q_z*H + q_y*d| << 1
            // relative error is O((q_y*W)^2) and O((q_z*H + q_y*d)^2)
            result = exp_I(-qyd)*(0.5 + mul_I(a)/6.);
        } else {
            // relative error is O((q_y*W)^2)
            result = exp_I(-qyd)*(1.0 + mul_I(a) - exp_I(a)) / (a * a);
        }
    } else {
        const complex_t gamma_p = (a + qyW2) * 0.5;
        const complex_t gamma_m = (a - qyW2) * 0.5;
        result = exp_I(gamma_m) * MathFunctions::sinc(gamma_p)
               - exp_I(gamma_p) * MathFunctions::sinc(gamma_m);
        result = mul_I(exp_I(-qyd)*result / (qyW2*2.));
    }
    return factor * result;
}

void FormFactorRipple2::onChange()
{
    mP_shape.reset(new RippleSawtooth(m_length, m_width, m_height, m_d));
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
