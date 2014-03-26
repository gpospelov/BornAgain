// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorWeighted.cpp
//! @brief     Implements class FormFactorWeighted.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorWeighted.h"

FormFactorWeighted::FormFactorWeighted()
{
    setName("FormFactorWeighted");
}

FormFactorWeighted::~FormFactorWeighted()
{
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        delete m_form_factors[index];
    }
}

FormFactorWeighted* FormFactorWeighted::clone() const
{
    FormFactorWeighted *result = new FormFactorWeighted();
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        result->addFormFactor(*m_form_factors[index], m_weights[index]);
    }
    result->setName(getName());
    return result;
}

void FormFactorWeighted::addFormFactor(const IFormFactor& form_factor,
        double weight)
{
    m_form_factors.push_back(form_factor.clone());
    m_weights.push_back(weight);
}

void FormFactorWeighted::setAmbientMaterial(const IMaterial *p_material)
{
    if(!p_material) return;
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        m_form_factors[index]->setAmbientMaterial(p_material);
    }
}

complex_t FormFactorWeighted::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const
{
    complex_t result(0.0, 0.0);
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        complex_t ff_evaluate = m_form_factors[index]->evaluate(k_i, k_f_bin,
                alpha_f_bin);
        result += m_weights[index]*ff_evaluate;
    }
    return result;
}

Eigen::Matrix2cd FormFactorWeighted::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin, const Bin1D &phi_f_bin) const
{
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        Eigen::Matrix2cd ff_evaluate = m_form_factors[index]->evaluatePol(
                k_i, k_f_bin, alpha_f_bin, phi_f_bin);
        result += m_weights[index]*ff_evaluate;
    }
    return result;
}

int FormFactorWeighted::getNumberOfStochasticParameters() const
{
    int result=0;
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        result += m_form_factors[index]->getNumberOfStochasticParameters();
    }
    return result;
}

