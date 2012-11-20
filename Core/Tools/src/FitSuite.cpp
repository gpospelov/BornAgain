#include "FitSuite.h"
#include "Exceptions.h"
#include "FitParameterLinked.h"
#include "ParameterPool.h"
#include "Experiment.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"


FitSuite::FitSuite() : m_minimizer(0), m_is_last_iteration(false), m_n_call(0), m_n_strategy(0)
{
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
    m_is_last_iteration = false;
    m_n_call = 0;
    m_n_strategy = 0;
}


/* ************************************************************************* */
// add pair of (experiment, real data) for consecutive simulation
/* ************************************************************************* */
void FitSuite::addExperimentAndRealData(Experiment *experiment, const OutputData<double > *real_data, const IChiSquaredModule *chi2_module)
{
    m_suite_kit.add(experiment, real_data, chi2_module);
}


/* ************************************************************************* */
// add fit parameter
/* ************************************************************************* */
void FitSuite::addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim)
{
    m_fit_parameters.addParameter(name, value, step, attlim);
}


/* ************************************************************************* */
// add fit strategy
/* ************************************************************************* */
void FitSuite::addFitStrategy(IFitSuiteStrategy *strategy)
{
    strategy->init(this);
    m_fit_strategies.push_back(strategy);
}


/* ************************************************************************* */
// Link defined FitMultiParameters with experiment parameters
/* ************************************************************************* */
void FitSuite::link_fit_parameters()
{
    // loop over all experiments defined
    for(size_t i_exp = 0; i_exp<m_suite_kit.size(); ++i_exp) {
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
    for(size_t i_par = 0; i_par<m_fit_parameters.size(); i_par++) {
        m_minimizer->setVariable(i_par, m_fit_parameters[i_par] );
    }

    // minimizing
    m_minimizer->minimize();
}


/* ************************************************************************* */
// run fit
/* ************************************************************************* */
void FitSuite::runFit()
{
    m_is_last_iteration = false;

    // linking fit parameters with parameters defined in the experiment
    link_fit_parameters();

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

    // calling observers again to let them to get results
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

    // caclulate chi2 value
    double chi_squared = m_suite_kit.getChiSquaredValue();

    notifyObservers();
    m_n_call++;
    return chi_squared;
}



