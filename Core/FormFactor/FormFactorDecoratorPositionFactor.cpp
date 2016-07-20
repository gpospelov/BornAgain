// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorPositionFactor.cpp
//! @brief     Implements class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorPositionFactor.h"
#include "BornAgainNamespace.h"
#include "ISampleVisitor.h"
#include "WavevectorInfo.h"

FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(
    const IFormFactor& form_factor, kvector_t position)
    : IFormFactorDecorator(form_factor), m_position(position)
{
    setName(BornAgain::FormFactorDecoratorPositionFactorType);
}

FormFactorDecoratorPositionFactor* FormFactorDecoratorPositionFactor::clone() const
{
    return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position);
}

void FormFactorDecoratorPositionFactor::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorDecoratorPositionFactor::evaluate(
        const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    complex_t pos_factor = getPositionFactor(q);
    return pos_factor * mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(
        const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    complex_t pos_factor = getPositionFactor(q);
    return pos_factor * mp_form_factor->evaluatePol(wavevectors);
}

complex_t FormFactorDecoratorPositionFactor::getPositionFactor(const cvector_t q) const
{
    complex_t qr = q.x() * m_position.x() + q.y() * m_position.y() + q.z() * m_position.z();
    return exp_I(qr);
}
