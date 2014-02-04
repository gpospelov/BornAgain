// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Distributions.h
//! @brief     Defines classes representing distributions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONS_H_
#define DISTRIBUTIONS_H_

#include "IParameterized.h"

//! @class IDistribution1D
//! @ingroup algorithms_internal
//! @brief Interface for 1 dimensional distributions
class BA_CORE_API_ IDistribution1D : public IParameterized
{
public:
    IDistribution1D() {}
    virtual ~IDistribution1D() {}

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const=0;

    //! get the mean of the distribution
    virtual double getMean() const=0;

protected:
    static void SignalBadInitialization(std::string distribution_name) const;
};

//! @class DistributionGate
//! @ingroup algorithms
//! @brief uniform distribution function with half width hwhm
class BA_CORE_API_ DistributionGate : public IDistribution1D
{
public:
	DistributionGate(double mean, double hwhm);
	virtual ~DistributionGate() {}

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const;

    //! get the mean of the distribution
    virtual double getMean() const {
    	return m_mean;
    }
private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_hwhm;
}

//! @class DistributionLorentz
//! @ingroup algorithms
//! @brief Lorentz distribution with half width hwhm
class BA_CORE_API_ DistributionLorentz : public IDistribution1D
{
public:
	DistributionLorentz(double mean, double hwhm);
	virtual ~DistributionLorentz() {}

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const;

    //! get the mean of the distribution
    virtual double getMean() const {
    	return m_mean;
    }
private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_hwhm;
}

//! @class DistributionGaussian
//! @ingroup algorithms
//! @brief Gaussian distribution with standard deviation std_dev
class BA_CORE_API_ DistributionGaussian: public IDistribution1D
{
public:
	DistributionGaussian(double mean, double std_dev);
	virtual ~DistributionGaussian() {}

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const;

    //! get the mean of the distribution
    virtual double getMean() const {
    	return m_mean;
    }
private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_std_dev;
}

//! @class DistributionLogNormal
//! @ingroup algorithms
//! @brief Log-normal distribution
class BA_CORE_API_ DistributionLogNormal: public IDistribution1D
{
public:
	DistributionLogNormal(double mean_log, double sigma);
	virtual ~DistributionLogNormal() {}

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const;

    //! get the mean of the distribution
    virtual double getMean() const;
private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean_log;
    double m_sigma;
}

//! @class DistributionCosine
//! @ingroup algorithms
//! @brief Cosine distribution
class BA_CORE_API_ DistributionCosine: public IDistribution1D
{
public:
	DistributionCosine(double mean, double sigma);
	virtual ~DistributionCosine() {}

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const;

    //! get the mean of the distribution
    virtual double getMean() const {
    	return m_mean;
    }
private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_sigma;
}

#endif /* DISTRIBUTIONS_H_ */
