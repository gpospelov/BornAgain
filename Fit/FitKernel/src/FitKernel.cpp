// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitKernel.cpp
//! @brief     Implements class FitKernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitKernel.h"
#include "FitSuite.h"
#include "FitParameterLinked.h"
#include "IMinimizer.h"
#include "MessageService.h"
#include "FitSuitePrintObserver.h"
#include "MinimizerFactory.h"
#include "ChiSquaredModule.h"
#include <boost/bind.hpp>

FitKernel::FitKernel(FitSuite *fit_suite)
    : m_minimizer(MinimizerFactory::createMinimizer("Minuit2", "Migrad"))
    , m_is_last_iteration(false)
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
    delete m_minimizer;
    m_minimizer = 0;
    m_is_last_iteration = false;
}

//! Adds pair of (simulation, real data) for consecutive simulation
void FitKernel::addSimulationAndRealData(const GISASSimulation& simulation, const OutputData<double >& real_data, const IChiSquaredModule& chi2_module)
{
    m_fit_objects.add(simulation, real_data);
}

//! Adds fit parameter
void FitKernel::addFitParameter(const std::string& name, double value, double step, const AttLimits& attlim, double error)
{
    if(step <=0.0)
        step = value * getAttributes().getStepFactor();
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}

//! Adds fit parameter, step is calculated from initial parameter value
void FitKernel::addFitParameter(const std::string& name, double value, const AttLimits& attlim, double error)
{
    double step = value * getAttributes().getStepFactor();
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}

//! Adds fit strategy
void FitKernel::addFitStrategy(IFitStrategy *strategy)
{
    m_fit_strategies.addStrategy(strategy);
}

void FitKernel::addFitStrategy(const IFitStrategy &strategy)
{
    addFitStrategy(strategy.clone());
}

void FitKernel::setMinimizer(IMinimizer *minimizer)
{
    delete m_minimizer;
    m_minimizer = minimizer;
    if(!m_minimizer) {
        msglog(MSG::WARNING) << "FitSuite::setMinimizer() -> Warning. Attempt to set NULL minimizer.";
    }
}

void FitKernel::setMinimizer(const std::string &minimizer, const std::string &algorithm, const std::string &options)
{
    setMinimizer(MinimizerFactory::createMinimizer(minimizer, algorithm, options));
}

//! link FitMultiParameters with simulation parameters
void FitKernel::link_fit_parameters()
{
    ParameterPool *pool = m_fit_objects.createParameterTree();
    m_fit_parameters.link_to_pool(pool);
    msglog(MSG::DEBUG2) << "FitSuite::link_fit_parameters() -> Parameter pool:";
    msglog(MSG::DEBUG2) << *pool;
    delete pool;
}

bool FitKernel::check_prerequisites() const
{
    if( !m_minimizer ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No minimizer found.");
    if( !m_fit_objects.getNumberOfFitObjects() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No simulation/data description defined");
    if( !m_fit_parameters.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No fit parameters defined");
    return true;
}

void FitKernel::runFit()
{
    m_start_time =  boost::posix_time::microsec_clock::local_time();

    // check if all prerequisites are fullfilled before starting minimization
    check_prerequisites();

    m_is_last_iteration = false;

    // linking fit parameters with parameters defined in the simulation
    link_fit_parameters();

    // running minimization using strategies
    m_fit_strategies.minimize();

    // setting found values to the parameters (FIXME move to strategies)
    m_fit_parameters.setValues(m_minimizer->getValueOfVariablesAtMinimum());
    m_fit_parameters.setErrors(m_minimizer->getErrorOfVariables());

    // calling observers to let them to get results
    m_is_last_iteration = true;
    notifyObservers();

    m_end_time =  boost::posix_time::microsec_clock::local_time();
}


//! run single minimization round (called by FitSuiteStrategy)
void FitKernel::minimize()
{
    // initializing minimizer with fitting functions
    IMinimizer::function_chi2_t fun_chi2 = boost::bind(&FitSuiteChiSquaredFunction::evaluate, &m_function_chi2, _1);
    m_minimizer->setChiSquaredFunction( fun_chi2, m_fit_parameters.size());

    IMinimizer::function_gradient_t fun_gradient = boost::bind(&FitSuiteGradientFunction::evaluate, &m_function_gradient, _1, _2, _3);
    m_minimizer->setGradientFunction( fun_gradient, m_fit_parameters.size(), m_fit_objects.getSizeOfDataSet() );

    // initializing minimizer's parameters with the list of local fit parameters
    m_minimizer->setParameters(m_fit_parameters);

    // setting number of free parameters for proper chi2 normalization
    m_fit_objects.setNfreeParameters((int)m_fit_parameters.getNfreeParameters());

    // minimizing
    m_minimizer->minimize();

}


// get current number of minimization function calls
size_t FitKernel::getNCalls() const
{
    //return m_minimizer->getNCalls();
    // I don't know which function Minimizer calls (chi2 or gradient)
    return (m_function_chi2.getNCalls() ? m_function_chi2.getNCalls() : m_function_gradient.getNCalls());
}


// results to stdout
void FitKernel::printResults() const
{
    std::cout << std::endl;
    std::cout << "--- FitSuite::printResults -----------------------------------------------------" << std::endl;
    std::cout << " Chi2:" << std::scientific << std::setprecision(8) << m_fit_objects.getChiSquaredValue()
              << "    chi2.NCall:" << m_function_chi2.getNCalls()
              << "  grad.NCall:" << m_function_gradient.getNCalls() << ","
              << m_function_gradient.getNCallsGradient() << ","
              << m_function_gradient.getNCallsTotal() << " (neval, ngrad, total)" << std::endl;
    m_minimizer->printResults();
}


// set print level
//void FitKernel::initPrint(int print_every_nth)
//{
//    boost::shared_ptr<FitSuitePrintObserver > observer(new FitSuitePrintObserver(print_every_nth));
//    attachObserver(observer);
//}

//FitParameter *FitKernel::getFitParameter(const std::string &name)
//{
//    return getFitParameters()->getParameter(name);
//}

void FitKernel::fixAllParameters()
{
    getFitParameters()->fixAll();
}

void FitKernel::releaseAllParameters()
{
    getFitParameters()->releaseAll();
}

void FitKernel::setParametersFixed(const std::vector<std::string> &pars, bool is_fixed)
{
    getFitParameters()->setParametersFixed(pars, is_fixed);
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


