#ifndef STOCHASTICSAMPLEDPARAMETER_H
#define STOCHASTICSAMPLEDPARAMETER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   StochasticSampledParameter.h
//! @brief  Definition of StochasticSampledParameter class
//! @author Scientific Computing Group at FRM II
//! @date   22.08.2012

#include "IStochasticParameter.h"
#include "Exceptions.h"

//- -------------------------------------------------------------------
//! @class StochasticSampledParameter
//! @brief To have stochastic parameter beeing sampled between xmin and xmax values
//- -------------------------------------------------------------------
class StochasticSampledParameter : public StochasticParameter<double>
{
public:
    //! constructor with nbins, xmin, xmax
    StochasticSampledParameter(const StochasticParameter<double> &par, size_t nbins, double xmin, double xmax);
    //! constructor with nbin and nfwhm to derive xmin and xmax
    StochasticSampledParameter(const StochasticParameter<double> &par, size_t nbins, int nfwhm=3);
    virtual ~StochasticSampledParameter();

    //! return radom value of stochastic parameter
    virtual void setToRandom() { m_stochastic_parameter->setToRandom(); }

    //! return probability density
    virtual double probabilityDensity(double value) const { return m_stochastic_parameter->probabilityDensity(value); }

    //! return x-value for given bin
    double getBinValue(size_t ibin) const
    {
        if(ibin < m_nbins ) {
            return m_xmin + ibin*(m_xmax-m_xmin)/double(m_nbins-1);
        } else {
            throw LogicErrorException("StochasticSampledParameter::getBinValue() -> Error. Wrong bin number ");
        }
    }

    //! return probability value for given bin
    double probabilityBinDensity(size_t ibin) const { return m_stochastic_parameter->probabilityDensity(getBinValue(ibin)); }

    //! get the normalized probability for the given bin
    double getNormalizedProbability(size_t ibin) const;
    //! return number of bins
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
