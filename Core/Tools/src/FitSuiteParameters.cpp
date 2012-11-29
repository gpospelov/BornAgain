#include "FitSuiteParameters.h"
#include "Experiment.h"



FitSuiteParameters::FitSuiteParameters()
{
}


FitSuiteParameters::~FitSuiteParameters()
{
    clear();
}


// clear all defined parameters
void FitSuiteParameters::clear()
{
    for(parameters_t::iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        delete (*it);
    }
    m_parameters.clear();
}


// add fit parameter
void FitSuiteParameters::addParameter(const std::string &name, double value, double step, const AttLimits &attlim)
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) throw LogicErrorException("FitSuiteParameters:addtFitParameter() -> Error. Existing parameter '"+name+"'");
    }
    m_parameters.push_back(new FitParameterLinked(name, value, step, attlim) );
}


// return const fit parameter with given name
const FitParameter *FitSuiteParameters::getParameter(const std::string &name) const
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuiteParameters::getFitParameter() -> Error. No parameter with name '"+name+"'");
}

// return fit parameter with given name
FitParameter *FitSuiteParameters::getParameter(const std::string &name)
{
    for(parameters_t::iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuiteParameters::getFitParameter() -> Error. No parameter with name '"+name+"'");
}


// set values for all defined parameters
void FitSuiteParameters::setValues(const double *pars_values)
{
    int index(0);
    for(parameters_t::iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) (*it)->setValue(pars_values[index++]);
}


void FitSuiteParameters::setValues(const std::vector<double> &pars_values)
{
    if(pars_values.size() != m_parameters.size() ) throw OutOfBoundsException("FitSuiteParameters::setValues() -> Wrong size of array with parameter values");
    setValues(&pars_values[0]);
}

std::vector<double > FitSuiteParameters::getValues() const
{
    std::vector<double > buff;
    buff.resize(m_parameters.size(), 0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it)
    {
        buff.push_back((*it)->getValue());
    }
    return buff;
}



/* ************************************************************************* */
// linking fit parameters with pool parameters
/* ************************************************************************* */
void FitSuiteParameters::link_to_pool(const ParameterPool *pool)
{
    // linking fit parameter with whose pool parameters which match name of fit parameter
    // going through all fit parameters defined
    for(parameters_t::iterator it = m_parameters.begin(); it!= m_parameters.end(); ++it) {
        FitParameterLinked *par = dynamic_cast<FitParameterLinked *>((*it));
        if( !par ) throw LogicErrorException("FitSuiteParameters::link_to_experiment() -> Error! Can't cast to FitParameterLinked.");
        par->addMatchedParametersFromPool(pool);
    }
}


