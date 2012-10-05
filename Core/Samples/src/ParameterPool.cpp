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
// copy constructor for completeness
// declared private, to avoid unconscious copying of parameters that point to previous owner
/* ************************************************************************* */
ParameterPool::ParameterPool(const ParameterPool &other)
{
    m_map = other.m_map;
}

/* ************************************************************************* */
// assignment operator for completeness
// declared private, to avoid unconscious copying of parameters that point to previous owner
/* ************************************************************************* */
ParameterPool &ParameterPool::operator=(const ParameterPool &other)
{
    if( this != &other)
    {
        m_map = other.m_map;
    }
    return *this;
}

/* ************************************************************************* */
// Clear the parameter container
/* ************************************************************************* */
void ParameterPool::clear()
{
    m_map.clear();
}

/* ************************************************************************* */
// Registering parameter with given name. Name should be different for each
// register.
/* ************************************************************************* */
bool ParameterPool::registerParameter(const std::string &name, double *parameter_address)
{
    RealPar par(parameter_address);
    return addParameter(name, par);
}

bool ParameterPool::addParameter(const std::string &name, RealPar par)
{
    parametermap_t::iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
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
    new_pool->m_map = m_map;
    return new_pool;
}

/* ************************************************************************* */
// Clone method that adds a prefix to parameter's keys
/* ************************************************************************* */
ParameterPool *ParameterPool::cloneWithPrefix(const std::string &prefix)
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
void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *external_pool) const
{
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        external_pool->addParameter(prefix+it->first, it->second);
    }
}

/* ************************************************************************* */
ParameterPool::RealPar ParameterPool::getParameter(const std::string &name) const
{
    parametermap_t::const_iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
        return (*it).second;
    } else {
        std::cout << "ParameterPool::getParameter() -> Warning. No parameter with name '" << name << std::endl;
        return RealPar(0);
    }
}

/* ************************************************************************* */
// set parameter value
/* ************************************************************************* */
bool ParameterPool::setParameterValue(const std::string &name, double value)
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
int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)
{
    int npars(0);
    for(iterator_t it=begin(); it!= end(); it++) {
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
