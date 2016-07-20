// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorFactor.cpp
//! @brief     Implements class FormFactorDecoratorFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorFactor.h"
#include "ISampleVisitor.h"

FormFactorDecoratorFactor::FormFactorDecoratorFactor(const IFormFactor& form_factor,
                                                     const complex_t factor)
    : IFormFactorDecorator(form_factor), m_factor(factor)
{
    setName(BornAgain::FormFactorDecoratorFactorType);
}

FormFactorDecoratorFactor *FormFactorDecoratorFactor::clone() const
{
    return new FormFactorDecoratorFactor(*mp_form_factor, m_factor);
}

void FormFactorDecoratorFactor::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorDecoratorFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    return m_factor * mp_form_factor->evaluate(wavevectors);
}
