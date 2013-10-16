// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/src/FitSuiteParameters.cpp
//! @brief     Implements class FitSuiteParameters.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteParameters.h"
#include "Simulation.h"
#include "MessageService.h"
#include "MathFunctions.h"

//! clear all defined parameters
void FitSuiteParameters::clear()
{
    for(parameters_t::iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) delete (*it);
    m_parameters.clear();
}

//! Adds fit parameter
void FitSuiteParameters::addParameter(const std::string& name, double value, double step, const AttLimits& attlim, double error)
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) throw LogicErrorException("FitSuiteParameters:addtFitParameter() -> Error. Existing parameter '"+name+"'");
    }
    m_parameters.push_back(new FitParameterLinked(name, value, step, attlim, error) );
}

//! Returns fit parameter with given name.
const FitParameter *FitSuiteParameters::getParameter(const std::string& name) const
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuiteParameters::getFitParameter() -> "
                              "Error. No parameter with name '"+name+"'");
}


FitParameter *FitSuiteParameters::getParameter(const std::string& name)
{
    for(parameters_t::iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuiteParameters::getFitParameter() -> "
                              "Error. No parameter with name '"+name+"'");
}

//! Sets values for all defined parameters
void FitSuiteParameters::setValues(const double *pars_values)
{
    if( !valuesAreDifferrent(pars_values) ) {
        msglog(MSG::INFO) << "FitSuiteParameters::setValues() -> Warning! Small or absent change in parameter values.";
        for(size_t i_par=0; i_par<m_parameters.size(); ++i_par) {
            msglog(MSG::INFO) << "npar:"<< i_par << std::setprecision(10)
                           << " current:" << m_parameters[i_par]->getValue()
                           << " new: " << pars_values[i_par]
                           << " diff:" << (m_parameters[i_par]->getValue() -pars_values[i_par])/Numeric::double_epsilon;
        }
    }

    size_t index(0);
    for(parameters_t::iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( MathFunctions::isnan(pars_values[index]) ) {
            throw LogicErrorException("FitSuiteParameters::setValues() -> Error. Attempt to set nan '"+(*it)->getName() + std::string("'.") );
        }
        if( MathFunctions::isinf(pars_values[index]) ) {
            throw LogicErrorException("FitSuiteParameters::setValues() -> Error. Attempt to set inf '" + (*it)->getName()  + std::string("'."));
        }
        (*it)->setValue(pars_values[index]);
        index++;
    }
}

//! ?
void FitSuiteParameters::setValues(const std::vector<double>& pars_values)
{
    if(pars_values.size() != m_parameters.size() ) {
        std::ostringstream ostr;
        ostr << "FitSuiteParameters::setValues() -> Wrong size of array with parameter values " << pars_values.size()
             << ", number of parameters expected " << m_parameters.size() << std::endl;
        throw OutOfBoundsException(ostr.str());
    }
    setValues(&pars_values[0]);
}


void FitSuiteParameters::setErrors(const std::vector<double>& pars_errors)
{
    if(pars_errors.size() != m_parameters.size() ) {
        std::ostringstream ostr;
        ostr << "FitSuiteParameters::setErrors() -> Wrong size of array with parameter values " << pars_errors.size()
             << ", number of parameters expected " << m_parameters.size() << std::endl;
        throw OutOfBoundsException(ostr.str());
    }
    for(size_t i=0; i<m_parameters.size(); ++i) {
        m_parameters[i]->setError(pars_errors[i]);
    }
}


//! ?
std::vector<double > FitSuiteParameters::getValues() const
{
    std::vector<double > result;
    result.resize(m_parameters.size(), 0.0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        result.push_back((*it)->getValue());
    }
    return result;
}

//! ?
std::vector<double > FitSuiteParameters::getErrors() const
{
    std::vector<double > result;
    result.resize(m_parameters.size(), 0.0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        result.push_back((*it)->getError());
    }
    return result;
}

//! ?
size_t FitSuiteParameters::getNfreeParameters() const
{
    size_t result(0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( !(*it)->isFixed() ) result++;
    }
    return result;
}

//! linking fit parameters with pool parameters
void FitSuiteParameters::link_to_pool(const ParameterPool *pool)
{
    // linking fit parameter with whose pool parameters which match name of fit parameter
    // going through all fit parameters defined
    for(parameters_t::iterator it = m_parameters.begin(); it!= m_parameters.end(); ++it) {
        FitParameterLinked *par = dynamic_cast<FitParameterLinked *>((*it));
        if( !par ) throw LogicErrorException("FitSuiteParameters::link_to_pool() -> Error! Can't cast to FitParameterLinked.");
        par->addMatchedParametersFromPool(pool);
    }
}

//! ?
bool FitSuiteParameters::valuesAreDifferrent(const double *pars_values, double tolerance_factor) const
{
    size_t index(0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( !Numeric::areAlmostEqual(pars_values[index++], (*it)->getValue(), tolerance_factor )) return true;
    }
    return false;
}

//! ?
void FitSuiteParameters::printParameters() const
{
    int npar(0);
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it, ++npar) {
        std::cout << "   # "<< npar << " " << (*(*it)) << std::endl;
    }
}


