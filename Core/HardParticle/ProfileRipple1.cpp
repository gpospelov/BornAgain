// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/ProfileRipple1.cpp
//! @brief     Implements class ProfileRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ProfileRipple1.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealLimits.h"
#include "RealParameter.h"
#include "RippleCosine.h"

//! @brief Constructor of cosine ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileRipple1::ProfileRipple1(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

bool ProfileRipple1::check_initialization() const
{
    bool result(true);
    if (m_height <= 0.0 || m_width <= 0.0 || m_length <= 0.0) {
        std::ostringstream ostr;
        ostr << "ProfileRipple1() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

double ProfileRipple1::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Complex form factor.
complex_t ProfileRipple1::factor_yz(complex_t qy, complex_t qz) const
{
    complex_t factor = m_width / M_PI;

    // analytical expressions for some particular cases
    if (qz == 0.) {
        if (qy == 0.)
            return factor * M_PI_2 * m_height;
        complex_t aaa = qy * m_width / (M_TWOPI);
        complex_t aaa2 = aaa * aaa;
        if (aaa2 == 1.)
            return factor * M_PI_4 * m_height;
        return factor * M_PI_2 * m_height * MathFunctions::sinc(qy * m_width * 0.5) / (1.0 - aaa2);
    }

    // numerical integration otherwise
    const complex_t ay = qy * m_width / M_TWOPI;
    const complex_t az = complex_t(0, 1) * qz * (m_height / 2);

    const auto integrand = [&](double u) -> complex_t {
        return sin(u) * exp(az * std::cos(u)) * (ay == 0. ? u : sin(ay * u) / ay);
    };
    complex_t integral = m_integrator.integrate(integrand, 0, M_PI);
    return factor * integral * exp(az) * (m_height / 2);
}

void ProfileRipple1::onChange()
{
    mP_shape.reset(new RippleCosine(m_length, m_width, m_height));
}
