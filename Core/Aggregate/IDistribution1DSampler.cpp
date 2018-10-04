// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IDistribution1DSampler.h"
#include <random>

IDistribution1DSampler::~IDistribution1DSampler() =default;


double Distribution1DCauchySampler::randomSample() const
{
    // BornAgain Cauchy Distribution = std library Exponential distribution
    std::random_device rd; // random device class instance
    std::mt19937 gen(rd());
    std::exponential_distribution<double> expDist(m_lambda);
    double value = expDist(gen);

    std::bernoulli_distribution bernoulliDist(0.5);
    bool sign = bernoulliDist(gen);

    if(sign == true)
        return value;
    else
        return -value;
}

double Distribution1DGaussSampler::randomSample() const
{
    // BornAgain Gauss Distribution = std library Normal distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> normalDist(m_mean, m_stddev);

    return normalDist(gen);
}

double Distribution1DGateSampler::randomSample() const
{
    // BornAgain Gate Distribution = std library Uniform distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> uniformDist(m_a, m_b);

    return uniformDist(gen);
}
