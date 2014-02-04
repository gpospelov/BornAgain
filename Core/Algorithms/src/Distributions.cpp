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

#include <math.h>

//! Interface
void IDistribution1D::SignalBadInitialization(
	std::string distribution_name) const
{
	throw new ClassInitializationException(distribution_name +
			": not correctly initialized");
}

//! DistributionGate
DistributionGate::DistributionGate(double mean, double hwhm)
: m_mean(mean)
, m_hwhm(hwhm)
{
	checkInitialization();
}

double DistributionGate::probabilityDensity(double x) const
{
	if (std::abs(x - m_mean) > m_hwhm) return 0.0;
	return 1.0/(2.0*m_hwhm);
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
	checkInitialization();
}

double DistributionLorentz::probabilityDensity(double x) const
{
	return m_hwhm/(m_hwhm*m_hwhm + (x-m_mean)*(x-m_mean))/M_PI;
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
	checkInitialization();
}

double DistributionGaussian::probabilityDensity(double x) const
{
	double exponential = std::exp(-(x-m_mean)*(x-m_mean)
			/(2.0*m_std_dev*m_std_dev));
	return exponential/m_std_dev/std::sqrt(2.0*M_PI);
}

bool DistributionGaussian::checkInitialization() const
{
	bool result = true;
	if (m_std_dev <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionGaussian");
	return result;
}

//! DistributionLogNormal
DistributionLogNormal::DistributionLogNormal(double mean_log, double sigma)
: m_mean_log(mean_log)
, m_sigma(sigma)
{
	checkInitialization();
}

double DistributionLogNormal::probabilityDensity(double x) const
{
	double t = (std::log(x) - m_mean_log)/m_sigma;
	return std::exp(-t*t/2.0)/(x*m_sigma*std::sqrt(2.0*M_PI));
}

double DistributionLogNormal::getMean() const
{
	double exponent = m_mean_log + m_sigma*m_sigma/2.0;
	return std::exp(exponent);
}

bool DistributionLogNormal::checkInitialization() const
{
	bool result = true;
	if (m_sigma <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionLogNormal");
	return result;
}

//! DistributionLogNormal
DistributionCosine::DistributionCosine(double mean, double sigma)
: m_mean(mean)
, m_sigma(sigma)
{
	checkInitialization();
}

double DistributionCosine::probabilityDensity(double x) const
{
	return (1.0 + std::cos((x-m_mean)/m_sigma))/(m_sigma*2.0*M_PI);
}

bool DistributionCosine::checkInitialization() const
{
	bool result = true;
	if (m_sigma <= 0.0) result = false;
	if (!result) SignalBadInitialization("DistributionCosine");
	return result;
}
