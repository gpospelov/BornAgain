// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorGauss.h"
#include "BornAgainNamespace.h"
#include "Numeric.h"
#include "Pi.h"

FormFactorGauss::FormFactorGauss(double volume)
{
    m_height = std::pow(volume, 1.0/3.0);
    m_width = m_height;
    initialize();
}

FormFactorGauss::FormFactorGauss(double width, double height)
{
    m_width = width;
    m_height = height;
    initialize();
}

complex_t FormFactorGauss::evaluate_for_q(const cvector_t q) const
{
    complex_t qzHdiv2 = m_height * q.z() / 2.0;
    double qzh = q.z().real() * m_height;
    if (std::abs(qzh) > m_max_ql)
        return 0.0;
    double qxr = q.x().real() * m_width;
    if (std::abs(qxr) > m_max_ql)
        return 0.0;
    double qyr = q.y().real() * m_width;
    if (std::abs(qyr) > m_max_ql)
        return 0.0;

    complex_t z_part = exp_I(qzHdiv2) * m_height * std::exp(-qzh * qzh / 4.0 / Pi::PI);
    double radial_part = m_width * m_width * std::exp(-(qxr * qxr + qyr * qyr) / 4.0 / Pi::PI);
    complex_t result = radial_part * z_part;
    return result;
}

void FormFactorGauss::initialize()
{
    setName(BornAgain::FFGaussType);
    registerNonnegativeLength(BornAgain::Width, &m_width);
    registerNonnegativeLength(BornAgain::Height, &m_height);
    m_max_ql = std::sqrt(-4 * Pi::PI * std::log(Numeric::double_min) / 3.0);
}
