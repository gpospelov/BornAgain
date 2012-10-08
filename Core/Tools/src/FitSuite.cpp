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
    for(fitmultiparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
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
// linking defined FitMultiParameters with sample parameters from pool
// initialising minimiser's fit parameters
/* ************************************************************************* */
void FitSuite::init_fit_parameters()
{
    if( !m_experiment ) throw NullPointerException("FitSuite::init_fit_parameters() -> Error! Experiment is absent.");
    if( !m_minimizer ) throw NullPointerException("FitSuite::init_fit_parameters() -> Error! Minimizer is absent.");
    if( m_fit_params.empty() ) throw NullPointerException("FitSuite::init_fit_parameters() -> Error! No fit parameters defined");

    // Linking FitMultiParameters with sample parameters from parameter pool.
    ParameterPool *pool = m_experiment->createParameterTree();
    for(fitmultiparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        FitMultiParameter *par = (*it);
        // name of FitMultiParameter is used to find in the pool links to sample's parameters
        par->addMatchedParametersFromPool(par->getName(), pool);
    }

    // propagating fit parameters in the minimizer
    int npar(0);
    for(fitmultiparameters_t::iterator it = m_fit_params.begin(); it!= m_fit_params.end(); ++it) {
        m_minimizer->setVariable(npar++, (*it) );
    }

    delete pool;
}


/* ************************************************************************* */
// linking defined FitMultiParameters with sample parameters from pool
// initialising minimiser's fit parameters
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

    m_experiment->getSample()->walk_and_print();

    // initializing fit parameters
    init_fit_parameters();

    std::cout << m_fit_params[0]->getName() << std::endl;
    m_fit_params[0]->setValue(999);
    m_experiment->getSample()->walk_and_print();


    // initializing minimizer with fcn function belonging to given class
    m_minimizer->setFunction( std::bind1st(std::mem_fun(&FitSuite::functionToMinimize), this), m_fit_params.size() );

    // run minimizer
    m_minimizer->minimize();

}


/* ************************************************************************* */
// function to minimize
/* ************************************************************************* */
double FitSuite::functionToMinimize(const double *pars_current_values)
{
    std::cout << " FitSuit::functionToMinimize() -> Info. We are here." << std::endl;

    for(size_t i=0; i<m_fit_params.size(); ++i) {
        std::cout << i << " " << pars_current_values[i] << std::endl;
        m_fit_params[i]->setValue(pars_current_values[i]);
    }

    m_experiment->runSimulation();
    m_experiment->normalize();

    const OutputData<double> *p_simulated_data = m_experiment->getOutputData();
    double chi_squared = m_chi2_module->calculateChiSquared(p_simulated_data);

    std::cout << "chi squared = " << chi_squared << std::endl;
    return chi_squared;
}

