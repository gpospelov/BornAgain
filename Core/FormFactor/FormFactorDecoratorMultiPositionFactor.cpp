// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorMultiPositionFactor.cpp
//! @brief     Implements class FormFactorDecoratorMultiPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorMultiPositionFactor.h"
#include "BornAgainNamespace.h"
#include "ISampleVisitor.h"
#include "WavevectorInfo.h"

FormFactorDecoratorMultiPositionFactor::FormFactorDecoratorMultiPositionFactor(
    const IFormFactor &form_factor, std::vector<kvector_t> positions)
    : IFormFactorDecorator(form_factor), m_positions(positions)
{
    setName(BornAgain::FormFactorDecoratorMultiPositionFactorType);
}

FormFactorDecoratorMultiPositionFactor* FormFactorDecoratorMultiPositionFactor::clone() const
{
    return new FormFactorDecoratorMultiPositionFactor(*mp_form_factor, m_positions);
}

void FormFactorDecoratorMultiPositionFactor::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

double FormFactorDecoratorMultiPositionFactor::getVolume() const
{
    size_t nbr_particles = m_positions.size();
    return nbr_particles * IFormFactorDecorator::getVolume();
}

double FormFactorDecoratorMultiPositionFactor::getRadius() const
{
    return IFormFactorDecorator::getRadius();
}

complex_t FormFactorDecoratorMultiPositionFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    return getPositionsFactor(q) * mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorMultiPositionFactor::evaluatePol(
        const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    Eigen::Matrix2cd ff = mp_form_factor->evaluatePol(wavevectors);
    return getPositionsFactor(q) * ff;
}

complex_t FormFactorDecoratorMultiPositionFactor::getPositionsFactor(const cvector_t q) const
{
    complex_t result;
    for (size_t i = 0; i < m_positions.size(); ++i) {
        complex_t qr = q.x() * m_positions[i].x() + q.y() * m_positions[i].y()
                       + q.z() * m_positions[i].z();
        result += exp_I(qr);
    }
    return result;
}
