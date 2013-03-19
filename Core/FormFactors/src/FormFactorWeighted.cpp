// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorWeighted.cpp
//! @brief     Implements class FormFactorWeighted.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
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
    FormFactorWeighted *p_new = new FormFactorWeighted();
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        p_new->addFormFactor(*m_form_factors[index], m_weights[index]);
    }
    return p_new;
}

void FormFactorWeighted::addFormFactor(const IFormFactor& form_factor,
        double weight)
{
    m_form_factors.push_back(form_factor.clone());
    m_weights.push_back(weight);
}

void FormFactorWeighted::setAmbientRefractiveIndex(const complex_t &refractive_index)
{
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        m_form_factors[index]->setAmbientRefractiveIndex(refractive_index);
    }
}

complex_t FormFactorWeighted::evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    complex_t result(0.0, 0.0);
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        complex_t ff_evaluate = m_form_factors[index]->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
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
