// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/ProfileRipple2.cpp
//! @brief     Implements class ProfileRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/ProfileRipple2.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include "Fit/Tools/RealLimits.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/RippleSawtooth.h" // from Shapes/

//! @brief Constructor of triangular ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileRipple2::ProfileRipple2(double length, double width, double height, double asymmetry)
    : m_length(length), m_width(width), m_height(height), m_asymmetry(asymmetry)
{
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::AsymmetryLength, &m_asymmetry).setUnit(BornAgain::UnitsNm);
    onChange();
}

bool ProfileRipple2::check_initialization() const
{
    bool result(true);
    if (m_height <= 0.0 || m_width <= 0.0 || m_length <= 0.0) {
        std::ostringstream ostr;
        ostr << "ProfileRipple2() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

double ProfileRipple2::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Complex form factor.
complex_t ProfileRipple2::factor_yz(complex_t qy, complex_t qz) const
{
    complex_t result;
    const complex_t factor = m_height * m_width;
    const complex_t qyW2 = qy * m_width * 0.5;
    const complex_t qyd = qy * m_asymmetry;
    const complex_t qzH = qz * m_height;
    const complex_t a = qzH + qyd;
    // dimensionless scale factors
    const double a_scale = std::abs(a);
    const double w_scale = std::abs(qyW2);

    if (w_scale < 1.e-5) {    // |q_y*W| << 1
        if (a_scale < 1e-5) { // |q_y*W| << 1 && |q_z*H + q_y*d| << 1
            // relative error is O((q_y*W)^2) and O((q_z*H + q_y*d)^2)
            result = exp_I(-qyd) * (0.5 + mul_I(a) / 6.);
        } else {
            // relative error is O((q_y*W)^2)
            result = exp_I(-qyd) * (1.0 + mul_I(a) - exp_I(a)) / (a * a);
        }
    } else {
        const complex_t gamma_p = (a + qyW2) * 0.5;
        const complex_t gamma_m = (a - qyW2) * 0.5;
        result = exp_I(gamma_m) * MathFunctions::sinc(gamma_p)
                 - exp_I(gamma_p) * MathFunctions::sinc(gamma_m);
        result = mul_I(exp_I(-qyd) * result / (qyW2 * 2.));
    }
    return factor * result;
}

void ProfileRipple2::onChange()
{
    mP_shape.reset(new RippleSawtooth(m_length, m_width, m_height, m_asymmetry));
}
