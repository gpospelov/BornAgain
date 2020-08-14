// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IProfileRipple.cpp
//! @brief     Implements class ProfileRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/IProfileRipple.h"
#include "Core/HardParticle/Ripples.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/RippleCosine.h"
#include "Core/Shapes/RippleSawtooth.h"

// ************************************************************************** //
// interface IProfileRipple
// ************************************************************************** //

//! @brief Constructor of cosine ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
IProfileRipple::IProfileRipple(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    registerParameter("Length", &m_length).setUnit("nm").setNonnegative();
    registerParameter("Width", &m_width).setUnit("nm").setNonnegative();
    registerParameter("Height", &m_height).setUnit("nm").setNonnegative();
}

double IProfileRipple::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

complex_t IProfileRipple::evaluate_for_q(cvector_t q) const
{
    return factor_x(q.x()) * factor_yz(q.y(), q.z());
}

// ************************************************************************** //
// interface ProfileRipple1
// ************************************************************************** //

//! @brief Constructor of cosine ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileRipple1::ProfileRipple1(double length, double width, double height)
    : IProfileRipple(length, width, height)
{
    onChange();
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

// ************************************************************************** //
// interface ProfileRipple2
// ************************************************************************** //

//! @brief Constructor of triangular ripple.
//! @param length: length of the rectangular base in nanometers
//! @param width: width of the rectangular base in nanometers
//! @param height: height of the ripple in nanometers
ProfileRipple2::ProfileRipple2(double length, double width, double height, double asymmetry)
    : IProfileRipple(length, width, height), m_asymmetry(asymmetry)
{
    registerParameter("AsymmetryLength", &m_asymmetry).setUnit("nm");
    onChange();
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
