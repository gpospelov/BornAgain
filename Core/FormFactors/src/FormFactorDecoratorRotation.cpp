// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDecoratorRotation.cpp
//! @brief     Implements class FormFactorDecoratorRotation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorRotation.h"
#include "BornAgainNamespace.h"

#include <memory>

FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor &form_factor, const IRotation &transform)
    : IFormFactorDecorator(form_factor)
{
    setName(BornAgain::FormFactorDecoratorRotationType);
    m_transform = transform.getTransform3D();
}

FormFactorDecoratorRotation *FormFactorDecoratorRotation::clone() const
{
    std::unique_ptr<IRotation> P_rotation(IRotation::createRotation(m_transform));
    return new FormFactorDecoratorRotation(*mp_form_factor, *P_rotation);
}

void FormFactorDecoratorRotation::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo &wavevectors) const
{
    cvector_t rotated_ki = m_transform.transformedInverse(wavevectors.getKi());
    cvector_t rotated_kf = m_transform.transformedInverse(wavevectors.getKf());
    WavevectorInfo rotated_wavevectors(rotated_ki, rotated_kf);
    return mp_form_factor->evaluate(rotated_wavevectors);
}
