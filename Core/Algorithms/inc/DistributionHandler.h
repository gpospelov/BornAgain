// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DistributionHandler.h
//! @brief     Defines class DistributionHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONHANDLER_H_
#define DISTRIBUTIONHANDLER_H_

#include "IParameterized.h"
#include "ParameterDistribution.h"


class IDistribution1D;

//! @class DistributionHandler
//! @ingroup algorithms_internal
//! @brief Provides the functionality to average over parameter distributions
//! with weights
class BA_CORE_API_ DistributionHandler : public IParameterized
{
public:
	DistributionHandler();
	~DistributionHandler();

	//! add a sampled parameter distribution
	void addParameterDistribution(const std::string &param_name,
			const IDistribution1D &distribution, size_t nbr_samples,
			double sigma_factor=0.0);

	//! get the total number of parameter value combinations (product
	//! of the individual sizes of each parameter distribution
	size_t getTotalNumberOfSamples() const;

	//! set the parameter values of the simulation object to a specific
	//! combination of values, determined by the index (which must be smaller
	//! than the total number of combinations) and returns the weight
	//! associated with this combination of parameter values
	double setParameterValues(ParameterPool *p_parameter_pool, size_t index);
private:
	size_t m_nbr_combinations;
	std::vector<ParameterDistribution> m_distributions;
	std::vector<std::vector<ParameterSample> > m_cached_samples;
};


#endif /* DISTRIBUTIONHANDLER_H_ */
