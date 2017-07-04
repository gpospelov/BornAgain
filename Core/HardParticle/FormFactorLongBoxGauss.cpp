// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBoxGauss.cpp
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
#include "Box.h"
#include "MathFunctions.h"
#include "RealParameter.h"

FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFLongBoxGaussType);
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

complex_t FormFactorLongBoxGauss::evaluate_for_q(cvector_t q) const
{
    complex_t qxL2 = std::pow(m_length * q.x(), 2) / 2.0;
    complex_t qyWdiv2 = m_width * q.y() / 2.0;
    complex_t qzHdiv2 = m_height * q.z() / 2.0;

    return m_height * m_length * m_width * exp_I(qzHdiv2) * std::exp(-qxL2)
            * MathFunctions::sinc(qyWdiv2) * MathFunctions::sinc(qzHdiv2);
}

IFormFactor* FormFactorLongBoxGauss::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorLongBoxGauss slicedff(m_length, m_width,
                                    m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorLongBoxGauss::onChange()
{
    mP_shape.reset(new Box(m_length, m_width, m_height));
}
