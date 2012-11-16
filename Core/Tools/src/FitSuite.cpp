#include "FitSuite.h"
#include "Exceptions.h"
#include "FitParameterLinked.h"
#include "ParameterPool.h"
#include "Experiment.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"


FitSuite::FitSuite() : m_minimizer(0), m_chi2_module(0), m_is_last_iteration(false), m_n_call(0), m_n_strategy(0)
{
    m_chi2_module = new ChiSquaredModule();
}


FitSuite::~FitSuite()
{
    clear();
}


/* ************************************************************************* */
// clear all data completely
/* ************************************************************************* */
void FitSuite::clear()
{
    m_suite_kit.clear();
    m_fit_parameters.clear();
    for(fitstrategies_t::iterator it = m_fit_strategies.begin(); it!= m_fit_strategies.end(); ++it) delete (*it);
    m_fit_strategies.clear();
    delete m_minimizer;
    m_minimizer = 0;
    delete m_chi2_module;
    m_chi2_module = 0;
    m_is_last_iteration = false;
    m_n_call = 0;
    m_n_strategy = 0;
}


/* ************************************************************************* */
// add pair of (experiment, real data) for consecutive simulation
/* ************************************************************************* */
void FitSuite::addExperimentAndRealData(Experiment *experiment, const OutputData<double > *real_data)
{
    m_suite_kit.add(experiment, real_data);
}


/* ************************************************************************* */
// add fit parameter
/* ************************************************************************* */
void FitSuite::addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim)
{

    m_fit_parameters.addParameter(name, value, step, attlim);
}


///* ************************************************************************* */
//// get fit parameter
///* ************************************************************************* */
//FitMultiParameter * FitSuite::getFitParameter(const std::string &name)
//{
//    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
//        if( (*it)->getName() == name ) return (*it);
//    }
//    throw LogicErrorException("FitSuite::getFitParameter() -> No parameter with name '"+name+std::string("'"));
//}


/* ************************************************************************* */
// add fit strategy
/* ************************************************************************* */
void FitSuite::addFitStrategy(IFitSuiteStrategy *strategy)
{
    strategy->init(this);
    m_fit_strategies.push_back(strategy);
}


/* ************************************************************************* */
// set real data (create chi2 module owning real data)
/* ************************************************************************* */
//void FitSuite::setRealData(const OutputData<double> &data)
//{
//    delete m_chi2_module;
//    m_chi2_module = new ChiSquaredModule(data);
//}


/* ************************************************************************* */
// Linking defined FitMultiParameters with experiment parameters
/* ************************************************************************* */
void FitSuite::init_fit_parameters()
{
    for(size_t i_exp = 0; i_exp<m_suite_kit.size(); ++i_exp)
    {
        m_fit_parameters.link_to_experiment(m_suite_kit.getExperiment(i_exp));
    }
}


/* ************************************************************************* */
// run single minimization round
/* ************************************************************************* */
void FitSuite::minimize()
{
    // initializing minimizer with fcn function belonging to given class
    m_minimizer->setFunction( std::bind1st(std::mem_fun(&FitSuite::functionToMinimize), this), m_fit_parameters.size() );

    // propagating local fit parameters to the minimizer's internal list of parameters
    int index(0);
    for(FitSuiteParameters::const_iterator it = m_fit_parameters.begin(); it!= m_fit_parameters.end(); ++it) {
        m_minimizer->setVariable(index++, (*it) );
    }
    if( index==0 ) std::cout << "FitSuite::minimize() -> Warning. No parameters has been propagated to the minimizer " << std::endl;

    // minimizing
    m_minimizer->minimize();
}


/* ************************************************************************* */
// run fit
/* ************************************************************************* */
void FitSuite::runFit()
{
    m_is_last_iteration = false;

    // initializing fit parameters
    init_fit_parameters();

    // running minimizer
    if( m_fit_strategies.empty() ) {
        // running single minimization round
        minimize();
    } else {
        // execute several minimization rounds as defined in concrete strategies
        for(fitstrategies_t::iterator it = m_fit_strategies.begin(); it!= m_fit_strategies.end(); ++it) {
            std::cout << "FitSuite::runFit() -> Info. Running strategy #" << m_n_strategy << " '" << (*it)->getName() << "'" << std::endl;
            (*it)->execute();
            m_n_strategy++;
        }
    }

    // seting parameters to the optimum values found by the minimizer
    for(size_t i=0; i<m_fit_parameters.size(); ++i) m_fit_parameters[i]->setValue(m_minimizer->getValueOfVariableAtMinimum(i));

    m_is_last_iteration = true;
    notifyObservers();
}


/* ************************************************************************* */
// function to minimize
/* ************************************************************************* */
double FitSuite::functionToMinimize(const double *pars_current_values)
{
    // set fitting parameters to values suggested by the minimizer
    m_fit_parameters.setValues(pars_current_values);

    // run simulations
    m_suite_kit.runSimulation();

    double chi_squared(0);
    for(size_t i_exp = 0; i_exp<m_suite_kit.size(); ++i_exp)
    {
        const OutputData<double> *simulated_data = m_suite_kit.getSimulatedData(i_exp);
        const OutputData<double> *real_data = m_suite_kit.getRealData(i_exp);
        m_chi2_module->setRealData(*real_data);
        chi_squared += m_chi2_module->calculateChiSquared(simulated_data);
    }

    notifyObservers();
    m_n_call++;
    return chi_squared;
}



