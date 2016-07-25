// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.cpp
//! @brief     Implements standard mix-in ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterPool.h"
#include "Utils.h"
#include <cassert>
#include <iostream>
#include <sstream>

typedef std::map<std::string, RealParameterWrapper> parametermap_t;

//! Constructs an empty parameter pool.
ParameterPool::ParameterPool(IParameterized* parent)
    : m_parent(parent), m_map()
{}

//! Returns a literal clone.
ParameterPool* ParameterPool::clone() const
{
    ParameterPool* new_pool = new ParameterPool(m_parent);
    new_pool->m_map = m_map;
    return new_pool;
}


//! Returns a clone with _prefix_ added to every parameter key.

ParameterPool* ParameterPool::cloneWithPrefix(const std::string& prefix) const
{
    ParameterPool* new_pool = new ParameterPool(m_parent);
    for(auto it=m_map.begin(); it!= m_map.end(); ++it)
        new_pool->addParameter(prefix+it->first, it->second);
    return new_pool;
}

//! Registers parameter with given name.

void ParameterPool::registerParameter(const std::string& name,
                                      double* parameter_address, const AttLimits& limits)
{
    addParameter(name, RealParameterWrapper(m_parent, parameter_address, limits) );
}

//! Low-level routine.

void ParameterPool::addParameter(const std::string& name, RealParameterWrapper par)
{
    if ( !m_map.insert(parametermap_t::value_type(name, par)).second ) {
        print(std::cout);
        throw Exceptions::RuntimeErrorException(
            "ParameterPool::addParameter() -> Error! Parameter '"+
            name+"' is already registered");
    }
}

//! Copy parameters of given pool to the external pool while adding prefix to
//! local parameter keys

void ParameterPool::copyToExternalPool(const std::string& prefix,
                                       ParameterPool* external_pool) const
{
    for(auto it=m_map.begin(); it!= m_map.end(); ++it)
        external_pool->addParameter(prefix+it->first, it->second);
}

//! Returns parameter with given name.

RealParameterWrapper ParameterPool::getParameter(const std::string& name) const
{
    auto it = m_map.find(name);
    if( it==m_map.end() )
        throw Exceptions::LogicErrorException("ParameterPool::getParameter() -> Warning."
                                  " No parameter with name '"+name+"'");
    return (*it).second;
}

//! Returns vector of parameters which fit pattern.

std::vector<RealParameterWrapper> ParameterPool::getMatchedParameters(
        const std::string& wildcards) const
{
    std::vector<RealParameterWrapper > selected_parameters;
    // loop over all parameters in the pool
    for(auto it=m_map.begin(); it!= m_map.end(); ++it) {
        // (*it).first - parameter key, (*it).second - parameter itself
        // parameters whose key match pattern are added to selected_parameters
        if( Utils::String::MatchPattern( (*it).first, wildcards ) )
            selected_parameters.push_back((*it).second);
    }
    if( selected_parameters.empty() ) {
        report_find_matched_parameters_error(wildcards);
    }
    return selected_parameters;
}

//! Sets parameter value.

void ParameterPool::setParameterValue(const std::string& name, double value)
{
    RealParameterWrapper x = getParameter(name);
    if( x.isNull() )
        throw Exceptions::LogicErrorException("ParameterPool::setParameterValue() ->"
                                  " Error! Unitialized parameter '"+name+"'.");
    try {
        x.setValue(value);
    } catch(Exceptions::RuntimeErrorException) {
        report_set_value_error(name, value);
    }
}

//! Sets parameter value.

int ParameterPool::setMatchedParametersValue(const std::string& wildcards, double value)
{
    int npars(0);
    for(auto it=m_map.begin(); it!= m_map.end(); ++it) {
        if( Utils::String::MatchPattern( (*it).first, wildcards ) ) {
            try {
                (*it).second.setValue(value);
                npars++;
            } catch(Exceptions::RuntimeErrorException) {
                report_set_value_error((*it).first, value);
            }
        }
    }
    if(npars == 0) {
        report_find_matched_parameters_error(wildcards);
    }
    return npars;
}

std::vector<std::string> ParameterPool::getParameterNames() const
{
    std::vector<std::string> result;
    for (auto it=m_map.begin(); it!= m_map.end(); ++it)
        result.push_back(it->first);
    return result;
}

//! Prints content on the screen.

void ParameterPool::print(std::ostream& ostr) const
{
    const size_t number_of_pars_in_line(12);
    if( m_map.size() ) {
        // print in one line
        if(m_map.size() < number_of_pars_in_line) {
            ostr << "POOL_" << m_map.size();
            ostr << "(";
            for(auto it=m_map.begin(); it!= m_map.end(); ++it) {
                ostr << "'" << (*it).first << "'" << ":" << it->second.getValue() << " " ;
            }
            ostr << ")";
        // print in several lines
        } else {
            for(auto it=m_map.begin(); it!= m_map.end(); ++it) {
                ostr << "'" << (*it).first << "'" << ":" << it->second.getValue() << std::endl;
            }
        }
    } else {
        ostr << "POOL_0";
    }
}


std::string ParameterPool::get_error_message(const std::string& criteria) const
{
    std::ostringstream ostr;
    ostr << "No parameters satisfying  criteria '" << criteria
       << "' have been found. Existing keys are:" << std::endl;
    for(auto it=m_map.begin(); it!= m_map.end(); ++it)
        ostr << "'" << (*it).first << "'" << std::endl;
    return ostr.str();
}

void ParameterPool::report_find_matched_parameters_error(const std::string& pattern) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::find_matched_parameters_error() -> Error! ";
    ostr << "No parameters matching  pattern '" << pattern
       << "' have been found. Existing keys are:" << std::endl;
    for(auto it=m_map.begin(); it!= m_map.end(); ++it)
        ostr << "'" << (*it).first << "'" << std::endl;
    throw Exceptions::LogicErrorException(ostr.str());
}

void ParameterPool::report_set_value_error(const std::string& parname, double value) const
{
    std::ostringstream ostr;
    auto it=m_map.find(parname);
    assert(it!=m_map.end());
    ostr << "ParameterPool::set_value_error() -> Attempt to set value ";
    ostr << value;
    ostr << " for parameter '" << parname << "' failed. Out of bounds?";
    ostr << " Parameter limits " << (*it).second.getAttLimits() << ".\n";
    throw Exceptions::LogicErrorException(ostr.str());
}
