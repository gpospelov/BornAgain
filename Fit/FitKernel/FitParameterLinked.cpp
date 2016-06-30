// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitParameterLinked.cpp
//! @brief     Implements class FitParameterLinked.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterLinked.h"
#include "Utils.h"

FitParameterLinked::FitParameterLinked()
{
}

FitParameterLinked::FitParameterLinked(const std::string& name, double value, double step, const AttLimits& attlim, double error) : FitParameter(name, value, step, attlim, error)
{
}

//! Adds real parameter to the collection
void FitParameterLinked::addParameter(RealParameterWrapper par)
{
    if( !par.isNull() ) {
        m_pool_parameters.push_back(par);
    } else {
        throw LogicErrorException("FitMultiParameter::addParameter() -> Attempt to add null parameter");
    }
}

//! Adds parameters from pool which match given wildcard
void FitParameterLinked::addMatchedParametersFromPool(const ParameterPool *pool, const std::string& wildcard)
{
    std::string wildcard_to_use = getName();
    if( !wildcard.empty()) wildcard_to_use = wildcard;

    pool_parameters_t matched_pars = pool->getMatchedParameters(wildcard_to_use);
    m_pool_parameters.insert(m_pool_parameters.end(), matched_pars.begin(), matched_pars.end());

    if( matched_pars.empty() ) {
        throw LogicErrorException("FitMultiParameter::addMatchedParametersFromPool() -> Error! Failed to add anything from pool using wildcard '"+wildcard_to_use+"'");
    }
}

void FitParameterLinked::print(std::ostream& ostr) const
{
    FitParameter::print(ostr);
    ostr << "FitParameterLinked '" << getName() << "'" << " value:" << m_value << " collsize:" << m_pool_parameters.size();
//    if(m_parametercoll.size() ) {
//        ostr << " addresses: ";
//        for(parametercoll_t::const_iterator it=m_parametercoll.begin(); it!=m_parametercoll.end(); it++) {
//            parameter_t par = (*it);
//            ostr << par << " ";
//        }
//    }
}


