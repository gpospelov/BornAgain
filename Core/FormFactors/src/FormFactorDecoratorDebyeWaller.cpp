// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDecoratorDebyeWaller.cpp
//! @brief     Implements class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorDebyeWaller.h"
#include "BornAgainNamespace.h"

using namespace  BornAgain;

FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor,
                                                               double dw_factor)
    : IFormFactorDecorator(form_factor), m_h_dw_factor(dw_factor), m_r_dw_factor(dw_factor)
{
    initialize();
}

FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor,
                                                               double dw_h_factor,
                                                               double dw_r_factor)
    : IFormFactorDecorator(form_factor), m_h_dw_factor(dw_h_factor), m_r_dw_factor(dw_r_factor)
{
    initialize();
}

FormFactorDecoratorDebyeWaller *FormFactorDecoratorDebyeWaller::clone() const
{
    return new FormFactorDecoratorDebyeWaller(*mp_form_factor, m_h_dw_factor, m_r_dw_factor);
}

complex_t FormFactorDecoratorDebyeWaller::evaluate(const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    double qr2 = std::norm(q.x()) + std::norm(q.y());
    double qz2 = std::norm(q.z());
    double dw = std::exp(-qz2 * m_h_dw_factor - qr2 * m_r_dw_factor);
    return dw * mp_form_factor->evaluate(wavevectors);
}

bool FormFactorDecoratorDebyeWaller::check_initialization() const
{
    return true;
}

void FormFactorDecoratorDebyeWaller::init_parameters()
{
    clearParameterPool();
    registerParameter(HeightDWFactor, &m_h_dw_factor, AttLimits::n_positive());
    registerParameter(RadiusDWFactor, &m_r_dw_factor, AttLimits::n_positive());
}

void FormFactorDecoratorDebyeWaller::initialize()
{
    setName(FormFactorDecoratorDebyeWallerType);
    check_initialization();
    init_parameters();
}
