// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/ProfileBar.cpp
//! @brief     Implements class ProfileBar.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/ProfileBar.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/Box.h" // from Shapes/
#include "Core/Tools/MathFunctions.h"
#include "Fit/Tools/RealLimits.h"

//! @brief Constructor of elongated bar
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileBar::ProfileBar(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

bool ProfileBar::check_initialization() const
{
    bool result(true);
    if (m_height <= 0.0 || m_width <= 0.0 || m_length <= 0.0) {
        std::ostringstream ostr;
        ostr << "ProfileBar() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

double ProfileBar::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Complex form factor.
complex_t ProfileBar::factor_yz(complex_t qy, complex_t qz) const
{
    const complex_t qyWdiv2 = m_width * qy / 2.0;
    const complex_t qzHdiv2 = m_height * qz / 2.0;

    return m_height * m_width * exp_I(qzHdiv2) * MathFunctions::sinc(qyWdiv2)
           * MathFunctions::sinc(qzHdiv2);
}

void ProfileBar::onChange()
{
    mP_shape.reset(new Box(m_length, m_width, m_height));
}
