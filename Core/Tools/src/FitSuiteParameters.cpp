#include "FitSuiteParameters.h"
#include "Experiment.h"



FitSuiteParameters::FitSuiteParameters()
{
}


FitSuiteParameters::~FitSuiteParameters()
{
    clear();
}


/* ************************************************************************* */
// clear all defined parameters
/* ************************************************************************* */
void FitSuiteParameters::clear()
{
    for(parameters_t::iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        delete (*it);
    }
    m_parameters.clear();
}


/* ************************************************************************* */
// add fit parameter
/* ************************************************************************* */
void FitSuiteParameters::addParameter(const std::string &name, double value, double step, const AttLimits &attlim)
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) throw LogicErrorException("FitSuiteParameters:addtFitParameter() -> Error. Existing parameter '"+name+"'");
    }
    m_parameters.push_back(new FitMultiParameter(name, value, step, attlim) );
}


/* ************************************************************************* */
// return fit parameter with given name
/* ************************************************************************* */
const FitMultiParameter *FitSuiteParameters::getParameter(const std::string &name) const
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuiteParameters::getFitParameter() -> Error. No parameter with name '"+name+"'");
}

FitMultiParameter *FitSuiteParameters::getParameter(const std::string &name)
{
    for(parameters_t::iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuiteParameters::getFitParameter() -> Error. No parameter with name '"+name+"'");
}


/* ************************************************************************* */
// set values for all defined parameters
// they will be propagated further
/* ************************************************************************* */
void FitSuiteParameters::setValues(const double *pars_values)
{
    int index(0);
    for(parameters_t::iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) (*it)->setValue(pars_values[index++]);
}


/* ************************************************************************* */
// link fit parameters to parameters defined in experiment
/* ************************************************************************* */
void FitSuiteParameters::link_to_experiment(const Experiment *experiment)
{
    // accessing parameter pool of the sample
    ParameterPool *pool = experiment->createParameterTree();

    // linking FitParameter
    int index(0);
    for(parameters_t::iterator it = m_parameters.begin(); it!= m_parameters.end(); ++it) {
        FitMultiParameter *par = (*it);
        // name of FitMultiParameter is used to find in the pool links to sample's parameters
        par->addMatchedParametersFromPool(par->getName(), pool);
        index++;
    }
    if( index==0 ) std::cout << "FitSuiteParameters::link_to_experiment() -> Warning. No parameters has been propagated to the minimizer " << std::endl;

    delete pool;
}


