#include "FitParameterLinked.h"
#include "Utils.h"


FitParameterLinked::FitParameterLinked()
{

}


FitParameterLinked::FitParameterLinked(const std::string &name, double value, double step, const AttLimits &attlim) : FitParameter(name, value, step, attlim)
{

}


/* ************************************************************************* */
//! add real parameter to the collection
/* ************************************************************************* */
void FitParameterLinked::addParameter(PoolParameter_t par)
{
    if( !par.isNull() ) {
        m_parametercoll.push_back(par);
    } else {
        throw LogicErrorException("FitMultiParameter::addParameter() -> Attempt to add null parameter");
    }
}


/* ************************************************************************* */
//! add all real parameters which match given pattern ('*?' wildcards) to the collection of parameters
/* ************************************************************************* */
void FitParameterLinked::addMatchedParametersFromPool(const ParameterPool *pool)
{
    std::vector<ParameterPool::RealPar > matched_pars = pool->getMatchedParameters(getName());
    m_parametercoll.insert(m_parametercoll.end(), matched_pars.begin(), matched_pars.end());

    if( matched_pars.empty() ) {
        throw LogicErrorException("FitMultiParameter::addMatchedParametersFromPool() -> Error! Failed to add anything from pool using own name '"+getName()+"'");
    }
}


void FitParameterLinked::addMatchedParametersFromPool(const std::string &wildcard, const ParameterPool *pool)
{
    std::vector<ParameterPool::RealPar > matched_pars = pool->getMatchedParameters(wildcard);
    m_parametercoll.insert(m_parametercoll.end(), matched_pars.begin(), matched_pars.end());

    if( matched_pars.empty() ) {
        throw LogicErrorException("FitMultiParameter::addMatchedParametersFromPool() -> Error! Failed to add anything from pool using wildcard '"+wildcard+"'");
    }
}



void FitParameterLinked::print(std::ostream &ostr) const
{
    FitParameter::print(ostr);
    ostr << "FitParameterLinked '" << getName() << "'" << " value:" << m_value << " collsize:" << m_parametercoll.size();
//    if(m_parametercoll.size() ) {
//        ostr << " addresses: ";
//        for(parametercoll_t::const_iterator it=m_parametercoll.begin(); it!=m_parametercoll.end(); it++) {
//            parameter_t par = (*it);
//            ostr << par << " ";
//        }
//    }
}

