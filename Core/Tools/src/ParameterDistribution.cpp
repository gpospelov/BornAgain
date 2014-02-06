// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/ParameterDistribution.cpp
//! @brief     Implements class ParameterDistribution.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterDistribution.h"

#include "Exceptions.h"
#include "Distributions.h"

ParameterDistribution::ParameterDistribution(const std::string& name)
: IParameterized("ParameterDistribution")
, m_name(name)
, m_nbr_samples(0)
, m_sigma_factor(0.0)
{
	init_parameters();
}

ParameterDistribution::ParameterDistribution(
		const ParameterDistribution& other)
: IParameterized("ParameterDistribution")
, m_name(other.m_name)
, m_nbr_samples(other.m_nbr_samples)
, m_sigma_factor(other.m_sigma_factor)
{
	mP_distribution.reset(other.mP_distribution->clone());
	init_parameters();
}

ParameterDistribution::~ParameterDistribution()
{
}

ParameterDistribution& ParameterDistribution::operator=(
		const ParameterDistribution& other)
{
	if (this != &other) {
		m_name = other.m_name;
		m_nbr_samples = other.m_nbr_samples;
		m_sigma_factor = other.m_sigma_factor;
		mP_distribution.reset(other.mP_distribution->clone());
		init_parameters();
	}
	return *this;
}

void ParameterDistribution::setDistribution(const IDistribution1D& distribution,
		size_t nbr_samples, double sigma_factor)
{
	mP_distribution.reset(distribution.clone());
	m_nbr_samples = nbr_samples;
	if (sigma_factor < 0.0) {
		throw Exceptions::RuntimeErrorException(
				"ParameterDistribution::setDistribution: "
				"sigma factor cannot be negative");
	}
	m_sigma_factor = sigma_factor;
}

std::vector<ParameterSample> ParameterDistribution::generateSamples() const
{
	return mP_distribution->generateSamples(m_nbr_samples, m_sigma_factor);
}

void ParameterDistribution::init_parameters()
{
    clearParameterPool();
//    registerParameter("sigma_factor", &m_sigma_factor);
}
