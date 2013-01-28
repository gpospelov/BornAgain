#include "FitSuite.h"
#include "Exceptions.h"
#include "FitParameterLinked.h"
#include "ParameterPool.h"
#include "Experiment.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"
#include <boost/bind.hpp>


FitSuite::FitSuite() : m_minimizer(0), m_is_last_iteration(false)
{
    m_function_chi2.init(this);
    m_function_gradient.init(this);
    m_fit_strategies.init(this);
}


FitSuite::~FitSuite()
{
    clear();
}


// ----------------------------------------------------------------------------
// clear all data
// ----------------------------------------------------------------------------
void FitSuite::clear()
{
    m_fit_objects.clear();
    m_fit_parameters.clear();
    m_fit_strategies.clear();
    delete m_minimizer;
    m_minimizer = 0;
    m_is_last_iteration = false;
}


// ----------------------------------------------------------------------------
// add pair of (experiment, real data) for consecutive simulation
// ----------------------------------------------------------------------------
void FitSuite::addExperimentAndRealData(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module)
{
    m_fit_objects.add(experiment, real_data, chi2_module);
}


// ----------------------------------------------------------------------------
// add fit parameter
// ----------------------------------------------------------------------------
void FitSuite::addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim, double error)
{
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}


// ----------------------------------------------------------------------------
// add fit strategy
// ----------------------------------------------------------------------------
void FitSuite::addFitStrategy(IFitSuiteStrategy *strategy)
{
    m_fit_strategies.addStrategy(strategy);
}


// ----------------------------------------------------------------------------
// Link FitMultiParameters with experiment parameters
// ----------------------------------------------------------------------------
void FitSuite::link_fit_parameters()
{
    ParameterPool *pool = m_fit_objects.createParameterTree();
    m_fit_parameters.link_to_pool(pool);
    std::cout << "FitSuite::link_fit_parameters() -> Parameter pool:" << std::endl;
    std::cout << *pool << std::endl;
    std::cout << "----------------" << std::endl;
    delete pool;
}


// ----------------------------------------------------------------------------
// run fit
// ----------------------------------------------------------------------------
bool FitSuite::check_prerequisites() const
{
    if( !m_minimizer ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No minimizer found.");
    if( !m_fit_objects.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No experiment/data description defined");
    if( !m_fit_parameters.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No fit parameters defined");
    return true;
}


// ----------------------------------------------------------------------------
// run fit
// ----------------------------------------------------------------------------
void FitSuite::runFit()
{
    // check if all prerequisites are fullfilled before starting minimization
    check_prerequisites();

    m_is_last_iteration = false;

    // linking fit parameters with parameters defined in the experiment
    link_fit_parameters();

    // running minimization using strategies
    m_fit_strategies.minimize();

    // seting parameters to the optimum values found by the minimizer
    m_fit_parameters.setValues(m_minimizer->getValueOfVariablesAtMinimum());

    // calling observers to let them to get results
    m_is_last_iteration = true;
    notifyObservers();
}


// ----------------------------------------------------------------------------
// run single minimization round (called by FitSuiteStrategy)
// ----------------------------------------------------------------------------
void FitSuite::minimize()
{
    // initializing minimizer with fitting functions
    IMinimizer::function_chi2_t fun_chi2 = boost::bind(&FitSuiteChiSquaredFunction::evaluate, &m_function_chi2, _1);
    m_minimizer->setChiSquaredFunction( fun_chi2, m_fit_parameters.size());

    IMinimizer::function_gradient_t fun_gradient = boost::bind(&FitSuiteGradientFunction::evaluate, &m_function_gradient, _1, _2, _3);
    m_minimizer->setGradientFunction( fun_gradient, m_fit_parameters.size(), m_fit_objects.getSizeOfDataSet() );

    // initializing minimizer's parameters with the list of local fit parameters
    m_minimizer->setParameters(m_fit_parameters);

    // setting number of free parameters for propper chi2 normalization
    m_fit_objects.setNfreeParameters(m_fit_parameters.getNfreeParameters());

    // minimizing
    m_minimizer->minimize();
}


// get current number of minimization function calls
size_t FitSuite::getNCalls() const
{
    //return m_minimizer->getNCalls();
    // I don't know which function Minimizer calls (chi2 or gradient)
    return (m_function_chi2.getNCalls() ? m_function_chi2.getNCalls() : m_function_gradient.getNCalls());
}


// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void FitSuite::printResults() const
{
    std::cout << std::endl;
    std::cout << "--- FitSuite::printResults --------------------------" << std::endl;
    std::cout << " Chi2:" << std::scientific << std::setprecision(8) << m_fit_objects.getChiSquaredValue()
              << "    chi2.NCall:" << m_function_chi2.getNCalls()
              << "  grad.NCall:" << m_function_gradient.getNCalls() << ","
              << m_function_gradient.getNCallsGradient() << ","
              << m_function_gradient.getNCallsTotal() << " (neval, ngrad, total)" << std::endl;
    m_fit_parameters.printParameters();
    m_minimizer->printResults();
}

