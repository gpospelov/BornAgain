// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDecoratorMultiPositionFactor.cpp
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

FormFactorDecoratorMultiPositionFactor::FormFactorDecoratorMultiPositionFactor(
        const IFormFactor& form_factor, std::vector<kvector_t> positions)
: IFormFactorDecorator(form_factor.clone())
, m_positions(positions)
{
    setName("FormFactorDecoratorMultiPositionFactor");
}

FormFactorDecoratorMultiPositionFactor*
FormFactorDecoratorMultiPositionFactor::clone() const
{
    return new FormFactorDecoratorMultiPositionFactor(
            *mp_form_factor, m_positions);
}

complex_t FormFactorDecoratorMultiPositionFactor::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    return getPositionsFactor(q)*mp_form_factor->
               evaluate(k_i, k_f_bin, alpha_f_bin);
}

Eigen::Matrix2cd FormFactorDecoratorMultiPositionFactor::evaluatePol(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin,
        const Bin1D &phi_f_bin) const
{
    cvector_t q = k_i - k_f_bin.getMidPoint();
    Eigen::Matrix2cd ff = mp_form_factor->evaluatePol(k_i, k_f_bin, alpha_f_bin, phi_f_bin);
    return getPositionsFactor(q)*ff;
}

complex_t FormFactorDecoratorMultiPositionFactor::getPositionsFactor(
        const cvector_t &q) const
{
    complex_t result;
    for (size_t i=0; i<m_positions.size(); ++i) {
        complex_t qr = q.x()*m_positions[i].x() + q.y()*m_positions[i].y()
                + q.z()*m_positions[i].z();
        result += std::exp(complex_t(0.0, 1.0)*qr);
    }
    return result;
}

