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

#include "FormFactorSphereGaussianRadius.h"

FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean,
                                                               double sigma)
: m_mean(mean)
, m_sigma(sigma)
, m_mean_r3(0.0)
, p_ff_sphere(0)
{
    setName("FormFactorSphereGaussianRadius");
    m_mean_r3 = calculateMeanR3();
    p_ff_sphere = new FormFactorFullSphere(m_mean_r3);
    init_parameters();
}

FormFactorSphereGaussianRadius* FormFactorSphereGaussianRadius::clone() const
{
    FormFactorSphereGaussianRadius *result =
        new FormFactorSphereGaussianRadius(m_mean, m_sigma);
    result->setName(getName());
    return result;
}

FormFactorSphereGaussianRadius::~FormFactorSphereGaussianRadius()
{
    delete p_ff_sphere;
}

int FormFactorSphereGaussianRadius::getNumberOfStochasticParameters() const
{
    return 2;
}

complex_t FormFactorSphereGaussianRadius::evaluate_for_q(
        const cvector_t& q) const
{
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double dw = std::exp(-q2*m_sigma*m_sigma/2.0);
    return dw*p_ff_sphere->evaluate_for_q(q);
}

double FormFactorSphereGaussianRadius::calculateMeanR3() const
{
    return std::pow(m_mean*(m_mean*m_mean+3.0*m_sigma*m_sigma),1.0/3.0);
}

void FormFactorSphereGaussianRadius::createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const
{
    assert(nbr_samples>1);
    double sigma_range = 2.0*m_sigma;
    double step = 2.0*sigma_range/(nbr_samples-1.0);
    double radius_start = m_mean-step*(nbr_samples/2); // 2 and not 2. is on purpose
    double total_prob = 0.0;
    for (size_t i=0; i<nbr_samples; ++i) {
        double radius = radius_start + (double)i*step;
        double probability = MathFunctions::Gaussian(radius, m_mean, m_sigma);
        form_factors.push_back(new FormFactorFullSphere(radius));
        probabilities.push_back(probability);
        total_prob += probability;
    }
    assert(total_prob);
    for (size_t i=0; i<probabilities.size(); ++i) {
        probabilities[i] /= total_prob;
    }
}

void FormFactorSphereGaussianRadius::init_parameters()
{
    clearParameterPool();
    registerParameter("mean_radius", &m_mean);
    registerParameter("sigma_radius", &m_sigma);
}
