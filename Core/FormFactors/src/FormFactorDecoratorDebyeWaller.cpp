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

FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor,
                                                               double dw_factor)
    : IFormFactorDecorator(form_factor), m_h_dw_factor(dw_factor), m_r_dw_factor(dw_factor)
{
    setName("FormFactorDecoratorDebyeWaller");
    check_initialization();
    init_parameters();
}

FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor,
                                                               double dw_h_factor,
                                                               double dw_r_factor)
    : IFormFactorDecorator(form_factor), m_h_dw_factor(dw_h_factor), m_r_dw_factor(dw_r_factor)
{
    setName("FormFactorDecoratorDebyeWaller");
    check_initialization();
    init_parameters();
}

FormFactorDecoratorDebyeWaller *FormFactorDecoratorDebyeWaller::clone() const
{
    FormFactorDecoratorDebyeWaller *result
        = new FormFactorDecoratorDebyeWaller(*mp_form_factor, m_h_dw_factor, m_r_dw_factor);
    result->setName(getName());
    return result;
}

complex_t FormFactorDecoratorDebyeWaller::evaluate(const cvector_t &k_i,
                                                   const Bin1DCVector &k_f_bin,
                                                   const Bin1D &alpha_f_bin) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    double qr2 = std::norm(q.x()) + std::norm(q.y());
    double qz2 = std::norm(q.z());
    double dw = std::exp(-qz2 * m_h_dw_factor - qr2 * m_r_dw_factor);
    return dw * mp_form_factor->evaluate(k_i, k_f_bin, alpha_f_bin);
}

bool FormFactorDecoratorDebyeWaller::check_initialization() const
{
    return true;
}

void FormFactorDecoratorDebyeWaller::init_parameters()
{
    clearParameterPool();
    registerParameter("hfactor", &m_h_dw_factor, AttLimits::n_positive());
    registerParameter("rfactor", &m_r_dw_factor, AttLimits::n_positive());
}
