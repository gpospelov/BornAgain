// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Distributions.h
//! @brief     Defines classes representing distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include "IParameterized.h"
#include "RealLimits.h"
#include "ParameterSample.h"
#include <vector>

//! Interface for 1 dimensional distributions.
//! @ingroup distribution_internal

class BA_CORE_API_ IDistribution1D : public IParameterized
{
public:
    IDistribution1D() {}
    virtual ~IDistribution1D() {}

    virtual IDistribution1D* clone() const;

    //! get the probability density for value x
    virtual double probabilityDensity(double x) const=0;

    //! get the mean of the distribution
    virtual double getMean() const=0;

    //! generate list of sampled values with their weight
    //! xmin, xmax for sample generations are deduced from sigma_factor and possible limits
    std::vector<ParameterSample> generateSamples(
        size_t nbr_samples, double sigma_factor=0.0, const RealLimits& limits = RealLimits()) const;

    //! generate list of sampled values with their weight within given xmin, xmax
    std::vector<ParameterSample> generateSamples(
        size_t nbr_samples, double xmin, double xmax) const;

    //! generate list of sample values
    //! @param nbr_samples number of values to generate
    //! @param sigma_factor parameter to derive min,max range for sample values
    //! @param limits
    //! @return vector of generated values
    virtual std::vector<double> generateValueList(size_t nbr_samples,
            double sigma_factor, const RealLimits& limits = RealLimits()) const=0;

    //! generate list of sample values
    //! @param nbr_samples number of values to generate
    //! @param xmin, xmax start and end value of the generated samples
    //! @return vector of generated values
    virtual std::vector<double> generateValues(size_t nbr_samples, double xmin, double xmax) const;

    //! generate a single sample containing the mean value and weight 1
    ParameterSample getMeanSample() const;

    //! signals that the distribution is in the limit case of a Dirac delta distribution
    virtual bool isDelta() const=0;

protected:
    //! this function is called during bad initialization of a subclass
    static void SignalBadInitialization(std::string distribution_name);

    //! modifies xmin and xmax if they are outside of limits
    void adjustMinMaxForLimits(double& xmin, double& xmax, const RealLimits& limits) const;

    //! generate list of sampled values with their weight from value list
    std::vector<ParameterSample> generateSamplesFromValues(
        const std::vector<double>& sample_values) const;
};


//! Uniform distribution function with half width hwhm.
//! @ingroup paramDistribution
class BA_CORE_API_ DistributionGate : public IDistribution1D
{
public:
    DistributionGate() : DistributionGate( 0., 1. ) {}
    DistributionGate(double min, double max);
    virtual ~DistributionGate() {}

    //! clone method
    virtual DistributionGate* clone() const { return new DistributionGate(m_min, m_max); }

    //! get the probability density for value x
    double probabilityDensity(double x) const final;

    //! get the mean of the distribution
    double getMean() const final { return (m_min+m_max)/2.0; }

    //! Returns the minimum value of the distribution
    double getMin() const { return m_min; }

    //! Returns the maximum value of the distribution
    double getMax() const { return m_max; }

    //! Returns list of sample values
    virtual std::vector<double> generateValueList(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    //! signals that the distribution is in the limit case of a Dirac delta distribution
    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_min;
    double m_max;
};


//! Lorentz distribution with half width hwhm.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionLorentz : public IDistribution1D
{
public:
    DistributionLorentz() : DistributionLorentz(0., 1.) {}
    DistributionLorentz(double mean, double hwhm);
    virtual ~DistributionLorentz() {}

    virtual DistributionLorentz* clone() const { return new DistributionLorentz(m_mean, m_hwhm); }

    //! get the probability density for value x
    double probabilityDensity(double x) const final;

    //! Returns the mean of the distribution
    double getMean() const final { return m_mean; }

    //! Returns the half width at half maximum
    double getHWHM() const { return m_hwhm; }

    //! generate list of sample values
    virtual std::vector<double> generateValueList(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    //! signals that the distribution is in the limit case of a delta distribution
    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_hwhm;
};


//! Gaussian distribution with standard deviation std_dev.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionGaussian: public IDistribution1D
{
public:
    DistributionGaussian() : DistributionGaussian(0., 1.) {}
    DistributionGaussian(double mean, double std_dev);
    virtual ~DistributionGaussian() {}

    //! clone method
    virtual DistributionGaussian* clone() const {
        return new DistributionGaussian(m_mean, m_std_dev); }

    //! get the probability density for value x
    double probabilityDensity(double x) const final;

    //! Returns the mean of the distribution
    double getMean() const final { return m_mean; }

    //! Returns the standard deviation
    double getStdDev() const { return m_std_dev; }

    //! generate list of sample values
    virtual std::vector<double> generateValueList(size_t nbr_samples,
            double sigma_factor, const RealLimits& limits = RealLimits()) const;

    //! signals that the distribution is in the limit case of a delta distribution
    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_std_dev;
};


//! Log-normal distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionLogNormal: public IDistribution1D
{
public:
    DistributionLogNormal(double scale_param) : DistributionLogNormal(1., scale_param) {}
    DistributionLogNormal(double median, double scale_param);
    virtual ~DistributionLogNormal() {}

    //! clone method
    virtual DistributionLogNormal* clone() const {
        return new DistributionLogNormal(m_median, m_scale_param); }

    //! get the probability density for value x
    double probabilityDensity(double x) const final;

    //! get the mean of the distribution
    double getMean() const final;

    //! Returns the median of the distribution
    double getMedian() const { return m_median; }

    //! Returns the scale parameter of the distribution
    double getScalePar() const { return m_scale_param; }

    //! generate list of sample values
    virtual std::vector<double> generateValueList(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    //! signals that the distribution is in the limit case of a delta distribution
    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_median;
    double m_scale_param;
};


//! Cosine distribution.
//! @ingroup paramDistribution

class BA_CORE_API_ DistributionCosine: public IDistribution1D
{
public:
    DistributionCosine() : DistributionCosine(0., 1.) {}
    DistributionCosine(double mean, double sigma);
    virtual ~DistributionCosine() {}

    //! clone method
    virtual DistributionCosine* clone() const { return new DistributionCosine(m_mean, m_sigma); }

    //! get the probability density for value x
    double probabilityDensity(double x) const final;

    //! Returns the mean of the distribution
    double getMean() const final { return m_mean; }

    //! Returns the sigma parameter of the distribution
    double getSigma() const { return m_sigma; }

    //! generate list of sample values
    virtual std::vector<double> generateValueList(
        size_t nbr_samples, double sigma_factor, const RealLimits& limits = RealLimits()) const;

    //! signals that the distribution is in the limit case of a delta distribution
    bool isDelta() const final;

protected:
    //! Registers some class members for later access via parameter pool
    void init_parameters();

private:
    //! check initialization
    bool checkInitialization() const;
    double m_mean;
    double m_sigma;
};

#endif // DISTRIBUTIONS_H
