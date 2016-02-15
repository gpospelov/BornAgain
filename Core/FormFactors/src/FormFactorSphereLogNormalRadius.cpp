// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorSphereGaussianRadius.cpp
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

using namespace  BornAgain;

FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(
        double mean, double scale_param, size_t n_samples)
: m_mean(mean)
, m_scale_param(scale_param)
, m_n_samples(n_samples)
, mp_distribution(0)
{
    setName(FormFactorSphereLogNormalRadiusType);
    mp_distribution = new DistributionLogNormal(mean, scale_param);
    check_initialization();
    init_parameters();
    init_vectors();
}

FormFactorSphereLogNormalRadius* FormFactorSphereLogNormalRadius::clone() const
{
    return new FormFactorSphereLogNormalRadius(m_mean, m_scale_param, m_n_samples);
}

FormFactorSphereLogNormalRadius::~FormFactorSphereLogNormalRadius()
{
    delete mp_distribution;
}

void FormFactorSphereLogNormalRadius::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorSphereLogNormalRadius::getRadius() const
{
    return m_mean;
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

bool FormFactorSphereLogNormalRadius::check_initialization() const
{
    return true;
}

void FormFactorSphereLogNormalRadius::init_parameters()
{
    clearParameterPool();
    registerParameter(MeanRadius, &m_mean, AttLimits::n_positive());
    registerParameter(ScaleParameter, &m_scale_param, AttLimits::n_positive());
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
