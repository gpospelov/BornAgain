// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereLogNormalRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorSphereLogNormalRadius.h"
#include "BornAgainNamespace.h"
#include "Distributions.h"

FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(
        double mean, double scale_param, size_t n_samples)
    : m_mean(mean)
    , m_scale_param(scale_param)
    , m_n_samples(n_samples)
    , mp_distribution(0)
{
    setName(BornAgain::FormFactorSphereLogNormalRadiusType);
    mp_distribution = new DistributionLogNormal(mean, scale_param);
    registerParameter(BornAgain::MeanRadius, &m_mean).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::ScaleParameter, &m_scale_param);
    if (!mp_distribution) return;
    // Init vectors:
    m_form_factors.clear();
    m_probabilities.clear();
    std::vector<ParameterSample> samples = mp_distribution->generateSamples(m_n_samples);
    for (size_t i=0; i<samples.size(); ++i) {
        double radius = samples[i].value;
        m_form_factors.push_back(new FormFactorFullSphere(radius));
        m_probabilities.push_back(samples[i].weight);
    }
}

FormFactorSphereLogNormalRadius::~FormFactorSphereLogNormalRadius()
{
    delete mp_distribution;
}

double FormFactorSphereLogNormalRadius::getRadialExtension() const
{
    return m_mean;
}

complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(const cvector_t q) const
{
    if (m_form_factors.size()<1)
        return 0.0;
    complex_t result(0.0);
    for (size_t i=0; i<m_form_factors.size(); ++i)
        result += m_form_factors[i]->evaluate_for_q(q) * m_probabilities[i];
    return result;
}
