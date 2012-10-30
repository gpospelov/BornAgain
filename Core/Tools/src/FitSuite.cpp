#include "FitSuite.h"
#include "Exceptions.h"
#include "FitMultiParameter.h"
#include "ParameterPool.h"
#include "Experiment.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"


FitSuite::FitSuite() : m_experiment(0), m_minimizer(0), m_chi2_module(0), m_is_last_iteration(false), m_n_call(0), m_n_strategy(0)
{
}


FitSuite::~FitSuite()
{
    clear();
}


/* ************************************************************************* */
// clear all and prepare for the next fit
/* ************************************************************************* */
void FitSuite::clear()
{
    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        delete (*it);
    }
    m_fit_params.clear();
    for(fitstrategies_t::iterator it = m_fit_strategies.begin(); it!= m_fit_strategies.end(); ++it) {
        delete (*it);
    }
    m_fit_strategies.clear();
    delete m_minimizer;
    delete m_chi2_module;
    m_is_last_iteration = false;
}


/* ************************************************************************* */
// add fit parameter
/* ************************************************************************* */
FitMultiParameter * FitSuite::addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim)
{
    // making MultiFitParameter for later access to sample's parameters
    FitMultiParameter *par = new FitMultiParameter(name, value, step, attlim);
    m_fit_params.push_back( par );
    return par;
}


/* ************************************************************************* */
// get fit parameter
/* ************************************************************************* */
FitMultiParameter * FitSuite::getFitParameter(const std::string &name)
{
    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        if( (*it)->getName() == name ) return (*it);
    }
    throw LogicErrorException("FitSuite::getFitParameter() -> No parameter with name '"+name+std::string("'"));
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
// set real data (create chi2 module owning real data)
/* ************************************************************************* */
void FitSuite::setRealData(const OutputData<double> &data)
{
    delete m_chi2_module;
    m_chi2_module = new ChiSquaredModule(data);
}


/* ************************************************************************* */
// Linking defined FitMultiParameters with sample parameters from pool.
// Initialising minimiser's fit parameters.
/* ************************************************************************* */
void FitSuite::init_fit_parameters()
{
    if( !m_experiment ) throw NullPointerException("FitSuite::init_fit_parameters() -> Error! Experiment is absent.");
    if( !m_minimizer ) throw NullPointerException("FitSuite::init_fit_parameters() -> Error! Minimizer is absent.");
    if( m_fit_params.empty() ) throw NullPointerException("FitSuite::init_fit_parameters() -> Error! No fit parameters defined");

    // Linking FitMultiParameters with sample parameters from parameter pool.
    ParameterPool *pool = m_experiment->createParameterTree();
    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        FitMultiParameter *par = (*it);
        // name of FitMultiParameter is used to find in the pool links to sample's parameters
        par->addMatchedParametersFromPool(par->getName(), pool);
    }
    delete pool;
}


/* ************************************************************************* */
// run single minimization round
/* ************************************************************************* */
void FitSuite::minimize()
{
    // propagating fit parameters to the minimizer
    int index(0);
    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        m_minimizer->setVariable(index++, (*it) );
    }

    // minimizing
    m_minimizer->minimize();
}


/* ************************************************************************* */
// run fit
/* ************************************************************************* */
void FitSuite::runFit()
{
    if( !m_experiment ) throw NullPointerException("FitSuite::runFit() -> Error! Experiment is missed.");
    if( !m_minimizer ) throw NullPointerException("FitSuite::runFit() -> Error! Minimizer is missed.");
    if( !m_chi2_module ) throw NullPointerException("FitSuite::runFit() -> Error! Chi2 module is missed.");
    if( m_fit_params.empty()) throw NullPointerException("FitSuite::runFit() -> Error! no fit parameters is defined.");

    m_is_last_iteration = false;

    // initializing fit parameters
    init_fit_parameters();

    // initializing minimizer with fcn function belonging to given class
    m_minimizer->setFunction( std::bind1st(std::mem_fun(&FitSuite::functionToMinimize), this), m_fit_params.size() );

    // running minimizer
    if( m_fit_strategies.empty() ) {
        // running single minimization round
        minimize();
    } else {
        // round several minimization rounds as defined in concrete strategies
        for(fitstrategies_t::iterator it = m_fit_strategies.begin(); it!= m_fit_strategies.end(); ++it) {
            std::cout << "FitSuite::runFit() -> Info. Running strategy '" << (*it)->getName() << "'" << std::endl;
            (*it)->execute();
            m_n_strategy++;
        }
    }

    // seting parameters to the optimum values found by the minimizer
    for(size_t i=0; i<m_fit_params.size(); ++i) m_fit_params[i]->setValue(m_minimizer->getValueOfVariableAtMinimum(i));

    m_is_last_iteration = true;
    notifyObservers();
}


/* ************************************************************************* */
// function to minimize
/* ************************************************************************* */
double FitSuite::functionToMinimize(const double *pars_current_values)
{
    if( m_fit_params.size() != m_minimizer->getNumberOfVariables() ) {
        throw RuntimeErrorException("FitSuite::functionToMinimize() -> Error! Wrong number of parameters (probably missed FitSuite's initialization).");
    }

    // set fitting parameters to values suggested by the minimizer
    for(size_t i=0; i<m_fit_params.size(); ++i) m_fit_params[i]->setValue(pars_current_values[i]);

    m_experiment->runSimulation();
    m_experiment->normalize();

    const OutputData<double> *p_simulated_data = m_experiment->getOutputData();
    double chi_squared = m_chi2_module->calculateChiSquared(p_simulated_data);

    notifyObservers();
    m_n_call++;
    return chi_squared;
}

