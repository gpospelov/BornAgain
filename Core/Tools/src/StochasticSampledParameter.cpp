#include "StochasticSampledParameter.h"
#include <iostream>



StochasticSampledParameter::StochasticSampledParameter(const StochasticParameter<double> &par, int nbins, double xmin, double xmax) :
    StochasticParameter<double>(0)
  , m_stochastic_parameter(par.clone())
  , m_nbins(nbins)
  , m_xmin(xmin)
  , m_xmax(xmax)
{

}


StochasticSampledParameter::StochasticSampledParameter(const StochasticParameter<double> &par, int nbins, int nfwhm) :
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


StochasticSampledParameter *StochasticSampledParameter::clone() const
{
    StochasticSampledParameter *p_new = new StochasticSampledParameter(*m_stochastic_parameter, m_nbins, m_xmin, m_xmax);
    return p_new;
}

