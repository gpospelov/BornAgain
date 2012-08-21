#include "ParameterPool.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iostream>
#include <sstream>


ParameterPool::ParameterPool()
{

}


ParameterPool::~ParameterPool()
{
    clear();
}



/* ************************************************************************* */
// copy constructor for completness
// declared private, to avoid unconscious copying of parameters, that pointing to previous owner
/* ************************************************************************* */
ParameterPool::ParameterPool(const ParameterPool &other)
{
//    m_map = 0;
//    if( other.m_map ) {
//        m_map = new parametermap_t;
//        // copying content of other's map
//        *m_map = *other.m_map;
//    }
    m_map = other.m_map;
}


/* ************************************************************************* */
// assignment operator for completness
// declared private, to avoid unconscious copying of parameters, that pointing to previous owner
/* ************************************************************************* */
ParameterPool &ParameterPool::operator=(const ParameterPool &other)
{
    if( this != &other)
    {
//        m_map = 0;
//        if( other.m_map ) {
//            m_map = new parametermap_t;
//            // copying content of other's map
//            *m_map = *other.m_map;
//        }
        m_map = other.m_map;
    }
    return *this;
}


/* ************************************************************************* */
// Clear the parameter container
/* ************************************************************************* */
void ParameterPool::clear()
{
//    if(m_map) {
//        m_map->clear();
//        delete m_map;
//        m_map=0;
//    }
    m_map.clear();
}


/* ************************************************************************* */
// Registering parameter with given name. Name should be different for each
// register.
/* ************************************************************************* */
bool ParameterPool::registerParameter(std::string name, double *parameter_address)
{
    RealPar par(parameter_address);
    return addParameter(name, par);
}


bool ParameterPool::addParameter(std::string name, RealPar par)
{
    // create map if not exist
    parametermap_t::iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
        // such parameter already registered, throw exception
        print(std::cout);
        std::ostringstream os;
        os << "ParameterPool::registerParameter() -> Warning! Registering parameter with same name '" << name << "'. Previous link will be replaced ";
        throw RuntimeErrorException(os.str());
    }
    return m_map.insert(parametermap_t::value_type(name, par ) ).second;
}


/* ************************************************************************* */
// Clone method. Clones everything.
/* ************************************************************************* */
ParameterPool *ParameterPool::clone()
{
    ParameterPool *new_pool = new ParameterPool;
//    if(m_map) {
//        new_pool->m_map = new parametermap_t;
//        *new_pool->m_map = *m_map;
//    }
    new_pool->m_map = m_map;
    return new_pool;
}


/* ************************************************************************* */
// Clone method with adding preffix to parameter's keys
/* ************************************************************************* */
ParameterPool *ParameterPool::cloneWithPrefix(std::string prefix)
{
    ParameterPool *new_pool = new ParameterPool;
    for(parametermap_t::iterator it=m_map.begin(); it!= m_map.end(); ++it)
    {
        new_pool->addParameter(prefix+it->first, it->second);
    }
    return new_pool;
}


/* ************************************************************************* */
// copy parameters of given pool to the external pool while adding prefix to
// local parameter keys
/* ************************************************************************* */
void ParameterPool::copyToExternalPool(std::string prefix, ParameterPool *external_pool)
{
    for(parametermap_t::iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        external_pool->addParameter(prefix+it->first, it->second);
    }
}


/* ************************************************************************* */
ParameterPool::RealPar ParameterPool::getParameter(std::string name) const
{
    parametermap_t::const_iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
        return (*it).second;
    } else {
        return RealPar(0);
    }
}


/* ************************************************************************* */
// set parameter value
/* ************************************************************************* */
bool ParameterPool::setParameterValue(std::string name, double value)
{
    RealPar x = getParameter(name);
    if( x.isNull() ) {
        std::cout << "ParameterPool::setParameterValue() -> Warning. No parameter with name '" << name << "'" << std::endl;
        throw LogicErrorException("ParameterPool::setParameterValue() -> Warning. No such parameter");
        return false;
    }
    x.setValue(value);
    return true;
}


/* ************************************************************************* */
// set parameter value
/* ************************************************************************* */
int ParameterPool::setMatchedParametersValue(std::string wildcards, double value)
{
    int npars(0);
    for(iterator_t it=begin(); it!= end(); it++) {
        // (*it).first - parameter key, (*it).second - parameter itself
        // parameters whose key match pattern is added to the FitMultiParameter container
        if( Utils::StringMatchText::WildcardPattern( (*it).first, wildcards ) ) {
            (*it).second.setValue(value);
            npars++;
        }
    }
    return npars;
}


/* ************************************************************************* */
// print content on the screen
/* ************************************************************************* */
//void ParameterPool::print(std::ostream &ostr) const
//{
//    ostr << "parameter pool: " << this;
//    ostr << "size(): " << m_map.size() << std::endl;
//    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); it++) {
//        std::cout << (*it).first << " " << (*it).second << std::endl;
//    }
//}

void ParameterPool::print(std::ostream &ostr) const
{
    // output depends on size of the pool
    size_t nsize = m_map.size();

    if(nsize) {
        // printing in one line
        if(nsize < 4) {
            ostr << "POOL_" << nsize;
            ostr << "(";
            for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); it++) {
                std::cout << "'" << (*it).first << "'" << ":" << it->second.getValue() << " " ;
            }
            ostr << ")";

        // printing in several lines
        } else {
            for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); it++) {
                std::cout << "'" << (*it).first << "'" << ":" << it->second.getValue() << std::endl;
            }
        }


    }
}

