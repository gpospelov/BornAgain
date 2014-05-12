// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorSphereGaussianRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorSphereLogNormalRadius.h"

#include "Distributions.h"

FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(
        double mean, double scale_param, size_t n_samples)
: m_mean(mean)
, m_scale_param(scale_param)
, m_n_samples(n_samples)
, mp_distribution(0)
{
    setName("FormFactorSphereLogNormalRadius");
    mp_distribution = new DistributionLogNormal(mean, scale_param);
    init_parameters();
    init_vectors();
}

FormFactorSphereLogNormalRadius* FormFactorSphereLogNormalRadius::clone() const
{
    FormFactorSphereLogNormalRadius *result =
        new FormFactorSphereLogNormalRadius(m_mean, m_scale_param, m_n_samples);
    result->setName(getName());
    return result;
}

FormFactorSphereLogNormalRadius::~FormFactorSphereLogNormalRadius()
{
    delete mp_distribution;
}

int FormFactorSphereLogNormalRadius::getNumberOfStochasticParameters() const
{
    return 2;
}

complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(
        const cvector_t& q) const
{
    if (m_form_factors.size()<1) return complex_t(0.0, 0.0);
    complex_t result(0.0, 0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        result += m_form_factors[i]->evaluate_for_q(q)
                * m_probabilities[i];
    }
    return result;
}

void FormFactorSphereLogNormalRadius::createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const
{
    (void)nbr_samples;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        const IFormFactor *p_ff = m_form_factors[i];
        double probability = m_probabilities[i];
        form_factors.push_back(p_ff->clone());
        probabilities.push_back(probability);
    }
}

double FormFactorSphereLogNormalRadius::getHeight() const
{
    if (m_form_factors.size()<1) return 0.0;
    double result = 0.0;
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        double height = m_form_factors[i]->getHeight();
        result = std::max(result, height);
    }
    return result;
}

void FormFactorSphereLogNormalRadius::init_parameters()
{
    clearParameterPool();
    registerParameter("mean_radius", &m_mean);
    registerParameter("scale_parameter", &m_scale_param);
}

void FormFactorSphereLogNormalRadius::init_vectors()
{
    if (!mp_distribution) return;
    m_form_factors.clear();
    m_probabilities.clear();
    std::vector<ParameterSample> samples =
            mp_distribution->generateSamples(m_n_samples);
    for (size_t i=0; i<samples.size(); ++i) {
        double radius = samples[i].value;
        m_form_factors.push_back(new FormFactorFullSphere(radius));
        m_probabilities.push_back(samples[i].weight);
    }
}