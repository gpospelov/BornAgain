// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDot.cpp
//! @brief     Implements class FormFactorDot.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorDot.h"
#include "BornAgainNamespace.h"
#include "Dot.h"
#include "RealParameter.h"

//! Constructor.
//! @param rscat: radius of a sphere with same forward scattering power, in nanometers
FormFactorDot::FormFactorDot(double radius) : m_radius(radius)
{
    setName(BornAgain::FFDotType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

complex_t FormFactorDot::evaluate_for_q(cvector_t) const
{
    return 4 * M_PI / 3 * pow(m_radius, 3);
}
