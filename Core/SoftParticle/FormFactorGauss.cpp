// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGaussSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/Box.h"
#include "Core/SoftParticle/FormFactorGauss.h"
#include <limits>

FormFactorGaussSphere::FormFactorGaussSphere(double mean_radius)
    : m_mean_radius(mean_radius)
{
    setName("FormFactorGaussSphere");
    registerParameter("MeanRadius", &m_mean_radius).setUnit("nm").setNonnegative();
    onChange();
}

complex_t FormFactorGaussSphere::evaluate_for_q(cvector_t q) const
{
    const double max_ql =
        std::sqrt(-4 * M_PI * std::log(std::numeric_limits<double>::min()) / 3);

    double qzh = q.z().real() * m_mean_radius;
    if (std::abs(qzh) > max_ql)
        return 0.0;
    double qxr = q.x().real() * m_mean_radius;
    if (std::abs(qxr) > max_ql)
        return 0.0;
    double qyr = q.y().real() * m_mean_radius;
    if (std::abs(qyr) > max_ql)
        return 0.0;

    return pow(m_mean_radius, 3) * std::exp(-(qxr * qxr + qyr * qyr + qzh * qzh) / 4.0 / M_PI);
}
