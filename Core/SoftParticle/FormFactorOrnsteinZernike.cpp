// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorOrnsteinZernike.cpp
//! @brief     Implements class FormFactorOrnsteinZernike.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorOrnsteinZernike.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include <limits>

FormFactorOrnsteinZernike::FormFactorOrnsteinZernike(double I0, double xi_xy, double xi_z)
{
    m_I0 = I0;
    m_xi_xy = xi_xy;
    m_xi_z = xi_z;
    setName(BornAgain::FFOrnsteinZernikeType);
}

complex_t FormFactorOrnsteinZernike::evaluate_for_q(cvector_t q) const
{
    complex_t denominator = 1.0 + m_xi_xy * m_xi_xy * q.magxy2() + m_xi_z * m_xi_z * q.z() * q.z();

    return std::sqrt(m_I0 / denominator);
}
