// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorDebyeBueche.cpp
//! @brief     Implements class FormFactorDebyeBueche.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorDebyeBueche.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include <limits>

FormFactorDebyeBueche::FormFactorDebyeBueche(double I0, double xi)
{
    m_I0 = I0;
    m_xi = xi;
    setName(BornAgain::FFDebyeBuecheType);
}

complex_t FormFactorDebyeBueche::evaluate_for_q(cvector_t q) const
{
    complex_t denominator = 1.0 + m_xi * m_xi * q.mag2();

    return std::sqrt(m_I0) / denominator;
}
