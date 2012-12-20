#include "FitSuiteParameters.h"
#include "Experiment.h"


double FitSuiteParameters::m_default_parameter_error=0.001;

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
void FitSuiteParameters::addParameter(const std::string &name, double value, double step, const AttLimits &attlim, double error)
{
    for(parameters_t::const_iterator it = m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( (*it)->getName() == name ) throw LogicErrorException("FitSuiteParameters:addtFitParameter() -> Error. Existing parameter '"+name+"'");
    }
    // defining default parameter error
    if(error == 0.0) error = value*m_default_parameter_error;
    m_parameters.push_back(new FitParameterLinked(name, value, step, attlim, error) );
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
// FIXME FitSuiteParameters::setValues  remove check for attempt to set parameter values
void FitSuiteParameters::setValues(const double *pars_values)
{
    if( !valuesAreDifferrent(pars_values) ) {
        std::cout << "FitSuiteParameters::setValues() -> Warning! Small or absent variation of parameters" << std::endl;
        for(size_t i=0; i<m_parameters.size(); i++)  std::cout << (m_parameters[i]->getValue() -pars_values[i]) << " " << Numeric::areAlmostEqual(m_parameters[i]->getValue(), pars_values[i]) << std::endl;
    }
    size_t index(0);
    for(parameters_t::iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) (*it)->setValue(pars_values[index++]);
}


void FitSuiteParameters::setValues(const std::vector<double> &pars_values)
{
    if(pars_values.size() != m_parameters.size() ) throw OutOfBoundsException("FitSuiteParameters::setValues() -> Wrong size of array with parameter values");
    setValues(&pars_values[0]);
}

std::vector<double > FitSuiteParameters::getValues() const
{
    std::vector<double > result;
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it)
    {
        result.push_back((*it)->getValue());
    }
    return result;
}


size_t FitSuiteParameters::getNfreeParameters() const
{
    size_t result(0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it)
    {
        if( !(*it)->isFixed() ) result++;
    }
    return result;
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


bool FitSuiteParameters::valuesAreDifferrent(const double *pars_values, double tolerance_factor) const
{
    size_t index(0);
    for(parameters_t::const_iterator it=m_parameters.begin(); it!=m_parameters.end(); ++it) {
        if( !Numeric::areAlmostEqual(pars_values[index++], (*it)->getValue(), tolerance_factor )) return true;
    }
    return false;
}



