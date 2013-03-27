// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/StochasticSampledParameter.h
//! @brief     Defines class StochasticSampledParameter.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef STOCHASTICSAMPLEDPARAMETER_H
#define STOCHASTICSAMPLEDPARAMETER_H

#include "IStochasticParameter.h"
#include "Exceptions.h"

//! To have stochastic parameter beeing sampled between xmin and xmax values.

class StochasticSampledParameter : public StochasticParameter<double>
{
 public:
    //! constructor with nbins, xmin, xmax
    StochasticSampledParameter(const StochasticParameter<double> &par, size_t nbins, double xmin, double xmax);
    //! constructor with nbin and nfwhm to derive xmin and xmax
    StochasticSampledParameter(const StochasticParameter<double> &par, size_t nbins, int nfwhm=3);
    virtual ~StochasticSampledParameter();

    //! Returns random value of stochastic parameter
    virtual void setToRandom() { m_stochastic_parameter->setToRandom(); }

    //! Returns probability density
    virtual double probabilityDensity(double value) const { return m_stochastic_parameter->probabilityDensity(value); }

    //! Returns ??-value for given bin
    double getBinValue(size_t ibin) const
    {
        if(ibin < m_nbins ) {
            return m_xmin + ibin*(m_xmax-m_xmin)/double(m_nbins-1);
        } else {
            throw LogicErrorException("StochasticSampledParameter::getBinValue() -> Error. Wrong bin number ");
        }
    }

    //! Returns probability value for given bin
    double probabilityBinDensity(size_t ibin) const { return m_stochastic_parameter->probabilityDensity(getBinValue(ibin)); }

    //! Returns the normalized probability for the given bin
    double getNormalizedProbability(size_t ibin) const;
    //! Returns number of bins
    size_t getNbins() const { return m_nbins; }

    //! clone method
    virtual StochasticSampledParameter *clone() const;

 private:
    StochasticParameter<double > *m_stochastic_parameter;
    size_t m_nbins;
    double m_xmin;
    double m_xmax;
};

#endif // STOCHASTICSAMPLEDPARAMETER_H
