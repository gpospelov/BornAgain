// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/ParameterPool.cpp
//! @brief     Implements class ParameterPool.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "ParameterPool.h"
#include "Exceptions.h"
#include "Utils.h"
#include "MessageService.h"

#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <sstream>

ParameterPool *ParameterPool::clone() const
{
    ParameterPool *new_pool = new ParameterPool();
    new_pool->m_map = m_map;
    return new_pool;
}

//! Clone method that adds a prefix to parameter's keys.

ParameterPool *ParameterPool::cloneWithPrefix(const std::string &prefix) const
{
    ParameterPool *new_pool = new ParameterPool();
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it)
    {
        new_pool->addParameter(prefix+it->first, it->second);
    }
    return new_pool;
}

//! Clear the parameter container.

void ParameterPool::clear()
{
    m_map.clear();
}

//! Register parameter with given name.

void ParameterPool::registerParameter(const std::string &name, double *parameter_address)
{
    parameter_t par(parameter_address);
    if( !addParameter(name, par) ) throw RuntimeErrorException("ParameterPool::registerParameter() -> Error! Can't register parameter");
}

//! Low-level routine.

bool ParameterPool::addParameter(const std::string &name, parameter_t par)
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

//! Copy parameters of given pool to the external pool while adding prefix to local parameter keys

void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *external_pool) const
{
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        external_pool->addParameter(prefix+it->first, it->second);
    }
}

//! Return parameter with given name.

ParameterPool::parameter_t ParameterPool::getParameter(const std::string &name) const
{
    parametermap_t::const_iterator it = m_map.find(name);
    if( it!=m_map.end() ) {
        return (*it).second;
    } else {
        throw LogicErrorException("ParameterPool::getParameter() -> Warning. No parameter with name '"+name+"'");
    }
}

//! Return vector of parameters which fit pattern.

std::vector<ParameterPool::parameter_t >  ParameterPool::getMatchedParameters(const std::string &wildcards) const
{
    std::vector<ParameterPool::parameter_t > selected_parameters;
    // loop over all parameters in the pool
    for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        // (*it).first - parameter key, (*it).second - parameter itself
        // parameters whose key match pattern is added to the FitMultiParameter container
        if( Utils::String::MatchPattern( (*it).first, wildcards ) ) {
            selected_parameters.push_back((*it).second);
        }
    }
    if( selected_parameters.empty() ) {
        msglog(MSG::FATAL) << "ParameterPool::getMatchedParameters() -> Warning! No parameters satisfying  criteria '" << wildcards << "' have been found";
        msglog(MSG::FATAL) << "Existing keys are:";
        for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) std::cout << (*it).first << std::endl;
        throw LogicErrorException("ParameterPool::getMatchedParameters() -> Error! No parameters with given wildcard.");
    }
    return selected_parameters;
}

//! Set parameter value.

bool ParameterPool::setParameterValue(const std::string &name, double value)
{
    parameter_t x = getParameter(name);
    if( x.isNull() ) {
        msglog(MSG::FATAL) << "ParameterPool::setParameterValue() -> Warning. No parameter with name '" << name << "'";
        throw LogicErrorException("ParameterPool::setParameterValue() -> Warning. No such parameter");
        return false;
    }
    x.setValue(value);
    return true;
}

//! Set parameter value.

int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)
{
    int npars(0);
    for(parametermap_t::iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        if( Utils::String::MatchPattern( (*it).first, wildcards ) ) {
            (*it).second.setValue(value);
            npars++;
        }
    }
    return npars;
}

int ParameterPool::fixRatioBetweenParameters(const std::string& to_change,
        const std::string& source, double ratio)
{
    int npars(0);
    std::string wildcard = (to_change[0] == '*' ? to_change : "*" + to_change);
    for(parametermap_t::iterator it=m_map.begin(); it!= m_map.end(); ++it) {
        if( Utils::String::MatchPattern( (*it).first, wildcard ) ) {
            std::string parametername = it->first;
            boost::algorithm::replace_last(parametername, to_change, source);
            try {
                parameter_t source = getParameter(parametername);
                (*it).second.setValue(source.getValue()*ratio);
                npars++;
            } catch (Exceptions::LogicErrorException &e) {}
        }
    }
    return npars;
}

//! Print content on the screen.

void ParameterPool::print(std::ostream &ostr) const
{
    const size_t number_of_pars_in_line(4);
    if( m_map.size() ) {
        // printing in one line
        if(m_map.size() < number_of_pars_in_line) {
            ostr << "POOL_" << m_map.size();
            ostr << "(";
            for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
                ostr << "'" << (*it).first << "'" << ":" << it->second.getValue() << " " ;
            }
            ostr << ")";
        // printing in several lines
        } else {
            for(parametermap_t::const_iterator it=m_map.begin(); it!= m_map.end(); ++it) {
                ostr << "'" << (*it).first << "'" << ":" << it->second.getValue() << std::endl;
            }
        }
    }
}
