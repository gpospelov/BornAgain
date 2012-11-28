#include "FitSuiteObjects.h"



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
    for(size_t i_exp = 0; i_exp<m_fit_objects.size(); ++i_exp) {
        const OutputData<double> *simulated_data = getSimulatedData(i_exp);
        const OutputData<double> *real_data = getRealData(i_exp);

        IChiSquaredModule *chi2_module = getChiSquaredModule(i_exp);

        chi2_module->setRealData(*real_data);
        double value = chi2_module->calculateChiSquared(simulated_data);
//        std::cout << " QQQ chi_squared " << i_exp << value << std::endl;
        chi_squared += value;
    }
//    std::cout << "QQQ chi_squared_sum " << chi_squared << std::endl;
    return chi_squared;
}

