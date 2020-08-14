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
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/HardParticle/Ripples.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/RippleSawtooth.h" // from Shapes/
#include "Core/Tools/MathFunctions.h"
#include "Fit/Tools/RealLimits.h"

//! @brief Constructor of triangular ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileRipple2::ProfileRipple2(double length, double width, double height, double asymmetry)
    : m_length(length), m_width(width), m_height(height), m_asymmetry(asymmetry)
{
    registerParameter("Length", &m_length).setUnit("nm").setNonnegative();
    registerParameter("Width", &m_width).setUnit("nm").setNonnegative();
    registerParameter("Height", &m_height).setUnit("nm").setNonnegative();
    registerParameter("AsymmetryLength", &m_asymmetry).setUnit("nm");
    onChange();
}

double ProfileRipple2::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Complex form factor.
complex_t ProfileRipple2::factor_yz(complex_t qy, complex_t qz) const
{
    return ripples::profile_yz_triangular(qy, qz, m_width, m_height, m_asymmetry);
}

void ProfileRipple2::onChange()
{
    mP_shape.reset(new RippleSawtooth(m_length, m_width, m_height, m_asymmetry));
}
