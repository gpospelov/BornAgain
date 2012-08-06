#include "WeightedFormFactor.h"

WeightedFormFactor::WeightedFormFactor()
{
}

WeightedFormFactor::~WeightedFormFactor()
{
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        delete m_form_factors[index];
    }
}

WeightedFormFactor* WeightedFormFactor::clone() const
{
    WeightedFormFactor *p_new = new WeightedFormFactor();
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        p_new->addFormFactor(*m_form_factors[index], m_weights[index]);
    }
    return p_new;
}

void WeightedFormFactor::addFormFactor(const IFormFactor& form_factor,
        double weight)
{
    m_form_factors.push_back(form_factor.clone());
    m_weights.push_back(weight);
}

void WeightedFormFactor::setAmbientRefractiveIndex(complex_t refractive_index)
{
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        m_form_factors[index]->setAmbientRefractiveIndex(refractive_index);
    }
}

complex_t WeightedFormFactor::evaluate(kvector_t k_i, kvector_t k_f) const
{
    complex_t result(0.0, 0.0);
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        complex_t ff_evaluate = m_form_factors[index]->evaluate(k_i, k_f);
        result += m_weights[index]*ff_evaluate;
    }
    return result;
}

complex_t WeightedFormFactor::evaluateForComplexkz(kvector_t k_i, kvector_t k_f,
        complex_t k_iz, complex_t k_fz) const
{
    complex_t result(0.0, 0.0);
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        result += m_weights[index]*m_form_factors[index]->evaluateForComplexkz(k_i, k_f, k_iz, k_fz);
    }
    return result;
}

int WeightedFormFactor::getNumberOfStochasticParameters() const
{
    int result=0;
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        result += m_form_factors[index]->getNumberOfStochasticParameters();
    }
    return result;
}
