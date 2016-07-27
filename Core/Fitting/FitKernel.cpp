// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitKernel.cpp
//! @brief     Implements class FitKernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AttLimits.h"
#include "FitKernel.h"
#include "FitSuite.h"
#include "Logger.h"
#include "MinimizerFactory.h"
#include "ParameterPool.h"

FitKernel::FitKernel(FitSuite* fit_suite)
    : m_minimizer(MinimizerFactory::createMinimizer("Minuit2", "Migrad"))
    , m_is_last_iteration(false)
    , m_is_interrupted(false)
    , m_fit_suite(fit_suite)
{
    m_function_chi2.init(this);
    m_function_gradient.init(this);
    m_fit_strategies.init(this);
}

FitKernel::~FitKernel()
{
    clear();
}

//! clear all data
void FitKernel::clear()
{
    m_fit_objects.clear();
    m_fit_parameters.clear();
    m_fit_strategies.clear();
    m_is_last_iteration = false;
    m_is_interrupted = false;
}

//! Adds pair of (simulation, real data) for consecutive simulation
void FitKernel::addSimulationAndRealData(const GISASSimulation& simulation,
                                         const OutputData<double>& real_data, double weight)
{
    m_fit_objects.add(simulation, real_data, weight);
}

//! Adds fit parameter, step is calculated from initial parameter value
void FitKernel::addFitParameter(const std::string& name, double value)
{
    addFitParameter(name, value, AttLimits::limitless());
}

//! Adds fit parameter, step is calculated from initial parameter value
void FitKernel::addFitParameter(const std::string& name, double value, const AttLimits& attlim,
                                double step, double error)
{
    if(step <=0.0)
        step = value * getOptions().getStepFactor();
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}

void FitKernel::addFitStrategy(const IFitStrategy& strategy)
{
    m_fit_strategies.addStrategy(strategy.clone());
}

void FitKernel::setMinimizer(IMinimizer* minimizer)
{
    if(!minimizer) {
        msglog(MSG::ERROR)
            << "FitSuite::setMinimizer() -> Error. Attempt to set nullptr minimizer.";
    }
    m_minimizer.reset(minimizer);
}

IMinimizer* FitKernel::getMinimizer()
{
    return m_minimizer.get();
}

void FitKernel::runFit()
{
    m_start_time =  boost::posix_time::microsec_clock::local_time();

    // check if all prerequisites are fullfilled before starting minimization
    check_prerequisites();

    m_is_last_iteration = false;

    // link fit parameters with parameters defined in the simulation
    link_fit_parameters();

    // run minimization using strategies
    m_fit_strategies.minimize();

    // call observers to let them to get results
    m_is_last_iteration = true;
    notifyObservers();

    m_end_time =  boost::posix_time::microsec_clock::local_time();
}

void FitKernel::minimize()
{
    // initialize minimizer with fitting functions
    IMinimizer::function_chi2_t fun_chi2 =
        [&] (const double* pars) {return m_function_chi2.evaluate(pars);};
    m_minimizer->setChiSquaredFunction( fun_chi2, m_fit_parameters.size());

    IMinimizer::function_gradient_t fun_gradient =
        [&] (const double* pars, unsigned int index, double* gradients)
        {
            return m_function_gradient.evaluate(pars, index, gradients);
        };
    m_minimizer->setGradientFunction(
        fun_gradient, m_fit_parameters.size(), m_fit_objects.getSizeOfDataSet() );

    // initialize minimizer's parameters with the list of local fit parameters
    m_minimizer->setParameters(m_fit_parameters);

    // setting number of free parameters for proper chi2 normalization
    m_fit_objects.setNfreeParameters((int)m_fit_parameters.getNfreeParameters());

    // minimize
    try {
        m_minimizer->minimize();
    } catch (int) {}

    // set found values to the parameters
    m_fit_parameters.setValues(m_minimizer->getValueOfVariablesAtMinimum());
    m_fit_parameters.setErrors(m_minimizer->getErrorOfVariables());
    m_fit_objects.runSimulations(); // we run simulation once again for best values found
}

FitSuiteObjects* FitKernel::getFitObjects()
{
    return &m_fit_objects;
}

const FitSuiteObjects* FitKernel::getFitObjects() const
{
    return &m_fit_objects;
}

FitSuiteParameters* FitKernel::getFitParameters()
{
    return &m_fit_parameters;
}

FitSuiteStrategies* FitKernel::getFitStrategies()
{
    return &m_fit_strategies;
}

bool FitKernel::isLastIteration() const
{
    return m_is_last_iteration;
}

// get current number of minimization function calls
size_t FitKernel::getNCalls() const
{
    //return m_minimizer->getNCalls();
    // I don't know which function Minimizer calls (chi2 or gradient)
    return m_function_chi2.getNCalls() ?
        m_function_chi2.getNCalls() : m_function_gradient.getNCalls();
}

size_t FitKernel::getCurrentStrategyIndex() const
{
    return m_fit_strategies.getCurrentStrategyIndex();
}

bool FitKernel::isInterrupted() const
{
    return m_is_interrupted;
}

void FitKernel::interruptFitting()
{
    m_is_interrupted = true;
}

void FitKernel::resetInterrupt()
{
    m_is_interrupted = false;
}

// results to stdout
void FitKernel::printResults() const
{
    std::cout << std::endl;
    std::cout
        << "--- FitSuite::printResults -----------------------------------------------------\n";
    std::cout << " Chi2:" << std::scientific << std::setprecision(8)
              << m_fit_objects.getChiSquaredValue()
              << "    chi2.NCall:" << m_function_chi2.getNCalls()
              << "  grad.NCall:" << m_function_gradient.getNCalls() << ","
              << m_function_gradient.getNCallsGradient() << ","
              << m_function_gradient.getNCallsTotal() << " (neval, ngrad, total)" << std::endl;
    m_minimizer->printResults();
}

FitOptions& FitKernel::getOptions()
{
    return m_fit_options;
}

void FitKernel::setOptions(const FitOptions& fit_options)
{
    m_fit_options = fit_options;
}

double FitKernel::getRunTime() const
{
    boost::posix_time::time_duration diff = m_end_time - m_start_time;
    return diff.total_milliseconds()/1000.;
}

void FitKernel::notifyObservers()
{
    m_fit_suite->notifyObservers();
}


bool FitKernel::check_prerequisites() const
{
    if( !m_minimizer ) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No minimizer found.");
    if( !m_fit_objects.getNumberOfFitObjects() ) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No simulation/data description defined");
    if( !m_fit_parameters.size() ) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No fit parameters defined");
    if( m_fit_objects.getSizeOfDataSet() == 0) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No elements to fit. "
        "Looks like whole detector is masked.");
    return true;
}

//! link FitMultiParameters with simulation parameters
void FitKernel::link_fit_parameters()
{
    const std::unique_ptr<ParameterPool> pool(m_fit_objects.createParameterTree());
    m_fit_parameters.link_to_pool(pool.get());
    msglog(MSG::DEBUG2) << "FitSuite::link_fit_parameters() -> Parameter pool:";
    msglog(MSG::DEBUG2) << *pool;
}
