#include "FitSuiteObjects.h"



FitSuiteObjects::FitSuiteObjects()
{
    setName("FitSuiteObjects");
    init_parameters();
}


/* ************************************************************************* */
// clear all data
/* ************************************************************************* */
void FitSuiteObjects::clear()
{
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) delete (*it);
    m_fit_objects.clear();
}


/* ************************************************************************* */
// add to kit pair of (experiment, real data) for consecutive simulation and chi2 module
/* ************************************************************************* */
void FitSuiteObjects::add(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module)
{
    m_fit_objects.push_back(new FitObject(experiment, real_data, chi2_module));
}


/* ************************************************************************* */
// loop through all defined experiments and run they simulation
/* ************************************************************************* */
void FitSuiteObjects::runSimulation()
{
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        (*it)->getExperiment()->runSimulation();
        (*it)->getExperiment()->normalize();
    }
}


/* ************************************************************************* */
// loop through all defined experiments and run they simulation
/* ************************************************************************* */
double FitSuiteObjects::getChiSquaredValue()
{
    double chi_squared(0);
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        chi_squared += (*it)->calculateChiSquared();
    }
    return chi_squared;
}


/* ************************************************************************* */
// add parameters from local pool to external pool
/* ************************************************************************* */
std::string FitSuiteObjects::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    (void)copy_number;
    // add own parameters
    // so far it is top object in our chain, and its without parameters, lets exclude its name from path
    //std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);
    std::string new_path = path;

    int ncopy(0);
    if(m_fit_objects.size()==1) ncopy=-1; // if we have only one object, lets get rid from copy number
    for(FitObjects_t::const_iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it, ++ncopy) {
        (*it)->addParametersToExternalPool(new_path, external_pool, ncopy);
    }

    return new_path;
}


void FitSuiteObjects::init_parameters()
{

}

