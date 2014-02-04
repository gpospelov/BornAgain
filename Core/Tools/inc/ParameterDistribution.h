// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterDistribution.h
//! @brief     Defines class ParameterDistribution.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERDISTRIBUTION_H_
#define PARAMETERDISTRIBUTION_H_

#include "ParameterSample.h"

#include <memory>
#include <string>
#include <vector>

class IDistribution1D;

class ParameterDistribution
{
public:
	ParameterDistribution(const std::string& name);
	~ParameterDistribution();

	void setDistribution(const IDistribution1D &distribution,
			size_t nbr_samples, double sigma_factor=0.0);

	size_t getNbrSamples() const {
		return m_nbr_samples;
	}

private:
	std::string m_name;
	size_t m_nbr_samples;
	double m_sigma_factor;
	std::auto_ptr<IDistribution1D> mP_distribution;
	std::vector<ParameterSample> m_samples;
};


#endif /* PARAMETERDISTRIBUTION_H_ */
