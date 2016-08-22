// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorMultiPositionFactor.cpp
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
#include <stdexcept>

FormFactorDecoratorMultiPositionFactor::FormFactorDecoratorMultiPositionFactor(
    const IFormFactor &form_factor, const std::vector<kvector_t>& positions)
    : IFormFactorDecorator(form_factor), m_positions(positions)
{
    setName(BornAgain::FormFactorDecoratorMultiPositionFactorType);
}

FormFactorDecoratorMultiPositionFactor* FormFactorDecoratorMultiPositionFactor::clone() const
{
    return new FormFactorDecoratorMultiPositionFactor(*mp_form_factor, m_positions);
}

double FormFactorDecoratorMultiPositionFactor::getVolume() const
{
    size_t nbr_particles = m_positions.size();
    return nbr_particles * IFormFactorDecorator::getVolume();
}

double FormFactorDecoratorMultiPositionFactor::getRadialExtension() const
{
    throw std::runtime_error(
        "Bug: Senseless call to FormFactorDecoratorMultiPositionFactor::getRadialExtension()");
}

complex_t FormFactorDecoratorMultiPositionFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    return getPositionsFactor(wavevectors) * mp_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactorDecoratorMultiPositionFactor::evaluatePol(
        const WavevectorInfo& wavevectors) const
{
    return getPositionsFactor(wavevectors) * mp_form_factor->evaluatePol(wavevectors);
}

complex_t FormFactorDecoratorMultiPositionFactor::getPositionsFactor(
    const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    complex_t result;
    for (const kvector_t& pos: m_positions)
        result += exp_I( pos.dot(q) );
    return result;
}
