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

#include "Core/HardParticle/ProfileRipple1.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/HardParticle/Ripples.h"
#include "Core/Shapes/RippleCosine.h" // from Shapes/
#include "Core/Tools/MathFunctions.h"
#include "Fit/Tools/RealLimits.h"

//! @brief Constructor of cosine ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileRipple1::ProfileRipple1(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    registerParameter("Length", &m_length).setUnit("nm").setNonnegative();
    registerParameter("Width", &m_width).setUnit("nm").setNonnegative();
    registerParameter("Height", &m_height).setUnit("nm").setNonnegative();
    onChange();
}

double ProfileRipple1::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Complex form factor.
complex_t ProfileRipple1::factor_yz(complex_t qy, complex_t qz) const
{
    return ripples::profile_yz_cosine(qy, qz, m_width, m_height);
}

void ProfileRipple1::onChange()
{
    mP_shape.reset(new RippleCosine(m_length, m_width, m_height));
}
