// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/StochasticSampledParameter.cpp
//! @brief     Implements class StochasticSampledParameter.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "StochasticSampledParameter.h"
#include <iostream>

StochasticSampledParameter::StochasticSampledParameter(const StochasticParameter<double> &par, size_t nbins, double xmin, double xmax) :
    StochasticParameter<double>(0)
  , m_stochastic_parameter(par.clone())
  , m_nbins(nbins)
  , m_xmin(xmin)
  , m_xmax(xmax)
{
}

StochasticSampledParameter::StochasticSampledParameter(const StochasticParameter<double> &par, size_t nbins, int nfwhm) :
    StochasticParameter<double>(0)
  , m_stochastic_parameter(par.clone())
  , m_nbins(nbins)
{
    m_xmin = m_stochastic_parameter->getAverage() - nfwhm*m_stochastic_parameter->getFWHM();
    m_xmax = m_stochastic_parameter->getAverage() + nfwhm*m_stochastic_parameter->getFWHM();

    if(m_xmin < 0) {
        std::cout << "StochasticSampledParameter::StochasticSampledParameter() -> Warning. xmin is negative " << m_xmin << " setting it to 1e-5" << std::endl;
        m_xmin = 1e-5; // isgisaxs trick
    }
}

StochasticSampledParameter::~StochasticSampledParameter()
{
    delete m_stochastic_parameter;
}

double StochasticSampledParameter::getNormalizedProbability(size_t ibin) const
{
    double total_prob = 0.0;
    for (size_t i=0; i<getNbins(); ++i) {
        total_prob += probabilityBinDensity(i);
    }
    return probabilityBinDensity(ibin)/total_prob;
}

StochasticSampledParameter *StochasticSampledParameter::clone() const
{
    StochasticSampledParameter *p_new = new StochasticSampledParameter(*m_stochastic_parameter, m_nbins, m_xmin, m_xmax);
    return p_new;
}
