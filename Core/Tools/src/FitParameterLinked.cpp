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
void FitParameterLinked::addParameter(ParameterPool::parameter_t par)
{
    if( !par.isNull() ) {
        m_parametercoll.push_back(par);
    } else {
        throw LogicErrorException("FitMultiParameter::addParameter() -> Attempt to add null parameter");
    }
}


/* ************************************************************************* */
//! add parameters from pool which match given wildcard
/* ************************************************************************* */
void FitParameterLinked::addMatchedParametersFromPool(const ParameterPool *pool, const std::string &wildcard)
{
    std::string wildcard_to_use = getName();
    if( !wildcard.empty()) wildcard_to_use = wildcard;

    PoolParameterColl_t matched_pars = pool->getMatchedParameters(wildcard_to_use);
    m_parametercoll.insert(m_parametercoll.end(), matched_pars.begin(), matched_pars.end());

    if( matched_pars.empty() ) {
        throw LogicErrorException("FitMultiParameter::addMatchedParametersFromPool() -> Error! Failed to add anything from pool using wildcard '"+wildcard_to_use+"'");
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

