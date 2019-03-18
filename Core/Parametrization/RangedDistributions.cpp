// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RangedDistributions.cpp
//! @brief     Implements classes representing ranged one-dimensional distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RangedDistributions.h"
#include "Distributions.h"
#include "ParameterSample.h"
#include <limits>

namespace {
template<class T>
std::unique_ptr<T> makeCopy(const T& item);

const double gate_stddev_factor = 2.0 * std::sqrt(3.0);
}

RangedDistribution::RangedDistribution()
    : m_n_samples(5)
    , m_sigma_factor(2.0)
    , m_limits(RealLimits::limitless())
{
    checkInitialization();
}

RangedDistribution::RangedDistribution(size_t n_samples, double sigma_factor,
                                       const RealLimits& limits)
    : m_n_samples(n_samples)
    , m_sigma_factor(sigma_factor)
    , m_limits(limits)
{
    checkInitialization();
}

RangedDistribution::RangedDistribution(size_t n_samples, double sigma_factor, double min,
                                       double max)
    : m_n_samples(n_samples)
    , m_sigma_factor(sigma_factor)
    , m_limits(RealLimits::limited(min, max))
{
    checkInitialization();
}

RangedDistribution::~RangedDistribution() = default;

std::vector<ParameterSample> RangedDistribution::generateSamples(double mean, double stddev) const
{
    return distribution(mean, stddev)->equidistantSamples(m_n_samples, m_sigma_factor, m_limits);
}

std::vector<std::vector<ParameterSample>>
RangedDistribution::generateSamples(std::vector<double> mean, std::vector<double> stddev) const
{
    if (mean.size() != stddev.size())
        throw std::runtime_error("Error in RangedDistribution::generateSamples: mean and variance "
                                 "vectors shall be of the same size");

    const size_t size = mean.size();

    std::vector<std::vector<ParameterSample>> result;
    result.resize(size);
    for (size_t i = 0; i < size; ++i) {
        auto distr = distribution(mean[i], stddev[i]);
        result[i] = distr->equidistantSamples(m_n_samples, m_sigma_factor, m_limits);
    }
    return result;
}

std::unique_ptr<IDistribution1D> RangedDistribution::distribution(double mean, double stddev) const
{
    if (stddev < 0.0)
        throw std::runtime_error(
            "Error in RangedDistribution::distribution: standard deviation is less than zero");
    return distribution_impl(mean, stddev);
}

void RangedDistribution::checkInitialization()
{
    if (m_n_samples < 1u)
        throw std::runtime_error("Error in RangedDistribution::checkInitialization: number of "
                                 "samples shall be positive");

    if (m_sigma_factor <= 0.0)
        throw std::runtime_error(
            "Error in RangedDistribution::checkInitialization: sigma factor shall be positive.");

    if (!m_limits.hasLowerAndUpperLimits())
        return;

    if (m_limits.lowerLimit() >= m_limits.upperLimit())
        throw std::runtime_error("Error in RangedDistribution::checkInitialization: lower limit "
                                 "shall not exceed the upper one.");
}

RangedDistributionGate* RangedDistributionGate::clone() const
{
    return makeCopy(*this).release();
}

std::unique_ptr<IDistribution1D>
RangedDistributionGate::distribution_impl(double mean, double stddev) const
{
    const double x_min = mean - gate_stddev_factor * stddev;
    const double x_max = mean + gate_stddev_factor * stddev;
    return std::make_unique<DistributionGate>(x_min, x_max);
}

RangedDistributionLorentz* RangedDistributionLorentz::clone() const
{
    return makeCopy(*this).release();
}

std::unique_ptr<IDistribution1D>
RangedDistributionLorentz::distribution_impl(double median, double hwhm) const
{
    return std::make_unique<DistributionLorentz>(median, hwhm);
}

RangedDistributionGaussian* RangedDistributionGaussian::clone() const
{
    return makeCopy(*this).release();
}

std::unique_ptr<IDistribution1D>
RangedDistributionGaussian::distribution_impl(double mean, double stddev) const
{
    return std::make_unique<DistributionGaussian>(mean, stddev);
}

RangedDistributionLogNormal* RangedDistributionLogNormal::clone() const
{
    return makeCopy(*this).release();
}

std::unique_ptr<IDistribution1D>
RangedDistributionLogNormal::distribution_impl(double mean, double stddev) const
{
    const double mean_2 = mean * mean;
    if (mean_2 <= std::numeric_limits<double>::min())
        throw std::runtime_error("Error in DistributionLogNormal::distribution: mean square value "
                                 "is less or indistinguishable from zero.");

    const double scale = std::sqrt(std::log(stddev * stddev / mean_2 + 1.0));
    const double median = mean * std::exp(- scale * scale / 2.0);
    return std::make_unique<DistributionLogNormal>(median, scale);
}

RangedDistributionCosine* RangedDistributionCosine::clone() const
{
    return makeCopy(*this).release();
}

std::unique_ptr<IDistribution1D>
RangedDistributionCosine::distribution_impl(double mean, double stddev) const
{
    return std::make_unique<DistributionCosine>(mean, stddev);
}

namespace {
template<class T>
std::unique_ptr<T> makeCopy(const T& item)
{
    return std::make_unique<T>(item.nSamples(), item.sigmaFactor(), item.limits());
}
}
