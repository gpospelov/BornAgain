// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorLongBoxGauss.cpp
//! @brief     Implements class FormFactorLongBoxGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLongBoxGauss.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(FFLongBoxGaussType);
    check_initialization();
    init_parameters();
}

FormFactorLongBoxGauss *FormFactorLongBoxGauss::clone() const
{
    return new FormFactorLongBoxGauss(m_length, m_width, m_height);
}

void FormFactorLongBoxGauss::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorLongBoxGauss::evaluate_for_q(const cvector_t q) const
{
    complex_t qxL2 = std::pow(m_length * q.x(), 2) / 2.0;
    complex_t qyWdiv2 = m_width * q.y() / 2.0;
    complex_t qzHdiv2 = m_height * q.z() / 2.0;

    return m_height * m_length * m_width * exp_I(qzHdiv2) * std::exp(-qxL2)
           * MathFunctions::sinc(qyWdiv2) * MathFunctions::sinc(qzHdiv2);
}

bool FormFactorLongBoxGauss::check_initialization() const
{
    return true;
}

void FormFactorLongBoxGauss::init_parameters()
{
    clearParameterPool();
    registerParameter(Length, &m_length, AttLimits::n_positive());
    registerParameter(Width,  &m_width,  AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}
