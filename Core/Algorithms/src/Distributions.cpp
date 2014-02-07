// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Distributions.cpp
//! @brief     Implements classes representing distributions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Distributions.h"

#include "MathFunctions.h"
#include "Exceptions.h"

#include <math.h>

std::vector<ParameterSample> IDistribution1D::generateSamples(
		size_t nbr_samples, double sigma_factor) const {
	if (nbr_samples == 0) {
		throw OutOfBoundsException("IDistribution1D::generateSamples: number "
				"of generated samples must be bigger than zero");
	}
	std::vector<double> sample_values = generateValueList(
			nbr_samples, sigma_factor);
	std::vector<ParameterSample> result;
	result.resize(nbr_samples);
	double norm_factor = 0.0;
	for (size_t i=0; i<nbr_samples; ++i) {
		double pdf = probabilityDensity(sample_values[i]);
		result[i].value = sample_values[i];
		result[i].weight = pdf;
		norm_factor += pdf;
	}
	if (norm_factor <= 0.0) {
		throw RuntimeErrorException("IDistribution1D::generateSamples: "
				"total probability must be bigger than zero");;
	}
	for (size_t i=0; i<nbr_samples; ++i) {
		result[i].weight /= norm_factor;
	}
	return result;
}

//! Interface
void IDistribution1D::SignalBadInitialization(std::string distribution_name)
{
	throw ClassInitializationException(distribution_name +
			": not correctly initialized");
}

//! DistributionGate
DistributionGate::DistributionGate(double mean, double hwhm)
: m_mean(mean)
, m_hwhm(hwhm)
{
	setName("DistributionGate");
	checkInitialization();
    init_parameters();
}

double DistributionGate::probabilityDensity(double x) const
{
	if (std::abs(x - m_mean) > m_hwhm) return 0.0;
	return 1.0/(2.0*m_hwhm);
}

std::vector<double> DistributionGate::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	(void)sigma_factor;
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		result.resize(nbr_samples);
		double xmin = m_mean - m_hwhm;
		double xmax = m_mean + m_hwhm;
		for (size_t i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

void DistributionGate::init_parameters()
{
    clearParameterPool();
    registerParameter("mean", &m_mean);
    registerParameter("hwhm", &m_hwhm);
}

bool DistributionGate::checkInitialization() const
{
	bool result = true;
	if (m_hwhm <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionGate");
	return result;
}

//! DistributionLorenz
DistributionLorentz::DistributionLorentz(double mean, double hwhm)
: m_mean(mean)
, m_hwhm(hwhm)
{
	setName("DistributionLorentz");
	checkInitialization();
    init_parameters();
}

double DistributionLorentz::probabilityDensity(double x) const
{
	return m_hwhm/(m_hwhm*m_hwhm + (x-m_mean)*(x-m_mean))/M_PI;
}

std::vector<double> DistributionLorentz::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		if (sigma_factor <= 0.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_mean - sigma_factor*m_hwhm;
		double xmax = m_mean + sigma_factor*m_hwhm;
		for (size_t i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

void DistributionLorentz::init_parameters()
{
    clearParameterPool();
    registerParameter("mean", &m_mean);
    registerParameter("hwhm", &m_hwhm);
}

bool DistributionLorentz::checkInitialization() const
{
	bool result = true;
	if (m_hwhm <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionLorentz");
	return result;
}

//! DistributionGaussian
DistributionGaussian::DistributionGaussian(double mean, double std_dev)
: m_mean(mean)
, m_std_dev(std_dev)
{
	setName("DistributionGaussian");
	checkInitialization();
    init_parameters();
}

double DistributionGaussian::probabilityDensity(double x) const
{
	double exponential = std::exp(-(x-m_mean)*(x-m_mean)
			/(2.0*m_std_dev*m_std_dev));
	return exponential/m_std_dev/std::sqrt(2.0*M_PI);
}

std::vector<double> DistributionGaussian::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		if (sigma_factor <= 0.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_mean - sigma_factor*m_std_dev;
		double xmax = m_mean + sigma_factor*m_std_dev;
		for (size_t i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

void DistributionGaussian::init_parameters()
{
    clearParameterPool();
    registerParameter("mean", &m_mean);
    registerParameter("std_dev", &m_std_dev);
}

bool DistributionGaussian::checkInitialization() const
{
	bool result = true;
	if (m_std_dev <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionGaussian");
	return result;
}

//! DistributionLogNormal
DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
: m_median(median)
, m_scale_param(scale_param)
{
	setName("DistributionLogNormal");
	checkInitialization();
    init_parameters();
}

double DistributionLogNormal::probabilityDensity(double x) const
{
	double t = std::log(x/m_median)/m_scale_param;
	return std::exp(-t*t/2.0)/(x*m_scale_param*std::sqrt(2.0*M_PI));
}

double DistributionLogNormal::getMean() const
{
	double exponent = m_scale_param*m_scale_param/2.0;
	return m_median*std::exp(exponent);
}

std::vector<double> DistributionLogNormal::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_median);
	}
	else {
		if (sigma_factor <= 0.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_median*std::exp(-sigma_factor*m_scale_param);
		double xmax = m_median*std::exp(sigma_factor*m_scale_param);
		for (size_t i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

void DistributionLogNormal::init_parameters()
{
    clearParameterPool();
    registerParameter("median", &m_median);
    registerParameter("scale_parameter", &m_scale_param);
}

bool DistributionLogNormal::checkInitialization() const
{
	bool result = true;
	if (m_scale_param <= 0.0) result = false;
	if (m_median <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionLogNormal");
	return result;
}

//! DistributionCosine
DistributionCosine::DistributionCosine(double mean, double sigma)
: m_mean(mean)
, m_sigma(sigma)
{
	setName("DistributionCosine");
	checkInitialization();
    init_parameters();
}

double DistributionCosine::probabilityDensity(double x) const
{
	return (1.0 + std::cos((x-m_mean)/m_sigma))/(m_sigma*2.0*M_PI);
}

std::vector<double> DistributionCosine::generateValueList(size_t nbr_samples,
		double sigma_factor) const
{
	std::vector<double> result;
	if (nbr_samples < 2) {
		result.push_back(m_mean);
	}
	else {
		if (sigma_factor <= 0.0 || sigma_factor > 2.0) sigma_factor = 2.0;
		result.resize(nbr_samples);
		double xmin = m_mean - sigma_factor*m_sigma*M_PI/2.0;
		double xmax = m_mean + sigma_factor*m_sigma*M_PI/2.0;
		for (size_t i=0; i<nbr_samples; ++i) {
			result[i] = xmin + i*(xmax-xmin)/(nbr_samples-1.0);
		}
	}
	return result;
}

void DistributionCosine::init_parameters()
{
    clearParameterPool();
    registerParameter("mean", &m_mean);
    registerParameter("sigma", &m_sigma);
}

bool DistributionCosine::checkInitialization() const
{
	bool result = true;
	if (m_sigma <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionCosine");
	return result;
}
