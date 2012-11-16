#include "FitMultiParameter.h"
#include "Utils.h"


FitMultiParameter::FitMultiParameter()
{

}


FitMultiParameter::FitMultiParameter(const std::string &name, double value, double step, const AttLimits &attlim) : FitParameter(name, value, step, attlim)
{

}


/* ************************************************************************* */
//! add real parameter to the collection
/* ************************************************************************* */
void FitMultiParameter::addParameter(parameter_t par)
{
    if( !par.isNull() ) {
        m_parametercoll.push_back(par);
    } else {
        throw LogicErrorException("FitMultiParameter::addParameter() -> Attempt to add null parameter");
    }
}


/* ************************************************************************* */
//! add real parameter with given name from the pool to the collection of parameters
/* ************************************************************************* */
void FitMultiParameter::addParameterFromPool(std::string parkey, const ParameterPool *pool)
{
    addParameter(pool->getParameter(parkey));
}


/* ************************************************************************* */
//! add all real parameters which match given pattern ('*?' wildcards) to the collection of parameters
/* ************************************************************************* */
void FitMultiParameter::addMatchedParametersFromPool(std::string wildcards, const ParameterPool *pool)
{
    // loop over all parameters in the pool
    int n_added_pars(0);
    for(ParameterPool::const_iterator_t it=pool->begin(); it!= pool->end(); it++) {
        // (*it).first - parameter key, (*it).second - parameter itself
        // parameters whose key match pattern is added to the FitMultiParameter container
        if( Utils::StringMatchText::WildcardPattern( (*it).first, wildcards ) ) {
            addParameter((*it).second);
            n_added_pars++;
        }
    }
    if(n_added_pars==0) {
        std::cout << "FitMultiParameter::addMatchedParametersFromPool() -> Warning! No parameters satisfying  criteria '" << wildcards << "' have been found" << std::endl;
        std::cout << "Existing keys are:" << std::endl;
        for(ParameterPool::const_iterator_t it=pool->begin(); it!= pool->end(); ++it) {
            std::cout << (*it).first << std::endl;
        }
        throw LogicErrorException("FitMultiParameter::addMatchedParametersFromPool() -> Error! No parameters with given wildcard.");
    }
}



void FitMultiParameter::print(std::ostream &ostr) const
{
    FitParameter::print(ostr);
//    ostr << "FitMultiParameter '" << getName() << "'" << " value:" << m_value << " collsize:" << m_parametercoll.size();
//    if(m_parametercoll.size() ) {
//        ostr << " addresses: ";
//        for(parametercoll_t::const_iterator it=m_parametercoll.begin(); it!=m_parametercoll.end(); it++) {
//            parameter_t par = (*it);
//            ostr << par << " ";
//        }
//    }
}

