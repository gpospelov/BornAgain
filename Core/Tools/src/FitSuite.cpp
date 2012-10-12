#include "FitSuite.h"
#include "Exceptions.h"
#include "FitMultiParameter.h"
#include "ParameterPool.h"
#include "Experiment.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"


FitSuite::FitSuite() : m_experiment(0), m_minimizer(0), m_chi2_module(0)
{
}


FitSuite::~FitSuite()
{
    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        delete (*it);
    }
    delete m_minimizer;
    delete m_chi2_module;
}


/* ************************************************************************* */
// add fit parameter
/* ************************************************************************* */
FitMultiParameter * FitSuite::addFitParameter(const std::string &name, double value, double step, double error)
{
    // making MultiFitParameter for later access to sample's parameters
    FitMultiParameter *par = new FitMultiParameter(name, value, step, error);
    m_fit_params.push_back( par );
    return par;
}

FitMultiParameter * FitSuite::addFitParameter(const std::string &name, double value, double step, const TRange<double> &range)
{
    // making MultiFitParameter for later access to sample's parameters
    FitMultiParameter *par = new FitMultiParameter(name, value, step);
    par->setLimits(range.getMin(), range.getMax() );
    m_fit_params.push_back( par );
    return par;
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

    // propagating fit parameters to the minimizer
    int npar(0);
    for(fitparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        m_minimizer->setVariable(npar++, (*it) );
    }

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
// run fit
/* ************************************************************************* */
void FitSuite::runFit()
{
    if( !m_experiment || !m_minimizer || !m_chi2_module || m_fit_params.empty()) throw NullPointerException("FitSuite::runFit() -> Error! Something is wrong.");

    // initializing fit parameters
    init_fit_parameters();

    // initializing minimizer with fcn function belonging to given class
    m_minimizer->setFunction( std::bind1st(std::mem_fun(&FitSuite::functionToMinimize), this), m_fit_params.size() );

    // run minimizer
    m_minimizer->minimize();

    // seting parameters to the optimum values found by the minimizer
    for(size_t i=0; i<m_fit_params.size(); ++i) m_fit_params[i]->setValue(m_minimizer->getValueOfVariableAtMinimum(i));

    notifyObservers();
}


/* ************************************************************************* */
// function to minimize
/* ************************************************************************* */
double FitSuite::functionToMinimize(const double *pars_current_values)
{
    // set fitting parameters to values suggested by the minimizer
    for(size_t i=0; i<m_fit_params.size(); ++i) m_fit_params[i]->setValue(pars_current_values[i]);

    m_experiment->runSimulation();
    m_experiment->normalize();

    const OutputData<double> *p_simulated_data = m_experiment->getOutputData();
    double chi_squared = m_chi2_module->calculateChiSquared(p_simulated_data);

    std::cout << "chi squared = " << chi_squared << std::endl;

    notifyObservers();
    return chi_squared;
}

