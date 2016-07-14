// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/ParameterDistribution.h
//! @brief     Declares class ParameterDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERDISTRIBUTION_H
#define PARAMETERDISTRIBUTION_H

#include "ParameterSample.h"
#include "IParameterized.h"

#include <memory>

class IDistribution1D;

class BA_CORE_API_ ParameterDistribution : public IParameterized
{
public:
    ParameterDistribution(const std::string &par_name,
                          const IDistribution1D &distribution,
                          size_t nbr_samples, double sigma_factor=0.0,
                          const AttLimits &limits = AttLimits());

    ParameterDistribution(const std::string &par_name,
                          const IDistribution1D &distribution,
                          size_t nbr_samples, double xmin, double xmax);

    ParameterDistribution(const ParameterDistribution &other);
    virtual ~ParameterDistribution();

    //! Overload assignment operator
    ParameterDistribution& operator=(const ParameterDistribution &other);

    ParameterDistribution& linkParameter(std::string par_name);

    //! get the main parameter's name
    std::string getMainParameterName() const;

    //! get number of samples for this distribution
    size_t getNbrSamples() const;

    //! get the sigma factor
    double getSigmaFactor() const;

    const IDistribution1D *getDistribution() const;

    //! generate list of sampled values with their weight
    std::vector<ParameterSample> generateSamples() const;

    //! get list of linked parameter names
    std::vector<std::string> getLinkedParameterNames() const;

    AttLimits getLimits() const;

    double getMinValue() const;
    double getMaxValue() const;

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();
private:
    std::string m_name;
    std::unique_ptr<IDistribution1D> mP_distribution;
    size_t m_nbr_samples;
    double m_sigma_factor;
    std::vector<std::string> m_linked_par_names;
    AttLimits m_limits;
    double m_xmin;
    double m_xmax;
};

inline std::string ParameterDistribution::getMainParameterName() const
{
    return m_name;
}

inline size_t ParameterDistribution::getNbrSamples() const
{
    return m_nbr_samples;
}

inline double ParameterDistribution::getSigmaFactor() const
{
    return m_sigma_factor;
}

inline const IDistribution1D *ParameterDistribution::getDistribution() const
{
    return mP_distribution.get();
}

inline std::vector<std::string> ParameterDistribution::getLinkedParameterNames() const
{
    return m_linked_par_names;
}

inline AttLimits ParameterDistribution::getLimits() const
{
    return m_limits;
}

inline double ParameterDistribution::getMinValue() const
{
    return m_xmin;
}

inline double ParameterDistribution::getMaxValue() const
{
    return m_xmax;
}

#endif // PARAMETERDISTRIBUTION_H
