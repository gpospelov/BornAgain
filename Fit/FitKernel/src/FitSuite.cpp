// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitSuite.cpp
//! @brief     Implements class FitSuite.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuite.h"
#include "FitParameterLinked.h"
#include "IMinimizer.h"
#include "MessageService.h"
#include "FitSuitePrintObserver.h"
#include "MinimizerFactory.h"
#include <boost/bind.hpp>

FitSuite::FitSuite()
    : m_minimizer(MinimizerFactory::createMinimizer("Minuit2", "Migrad"))
    , m_is_last_iteration(false)
{
    m_function_chi2.init(this);
    m_function_gradient.init(this);
    m_fit_strategies.init(this);
}

FitSuite::~FitSuite()
{
    clear();
}

//! clear all data
void FitSuite::clear()
{
    m_fit_objects.clear();
    m_fit_parameters.clear();
    m_fit_strategies.clear();
    delete m_minimizer;
    m_minimizer = 0;
    m_is_last_iteration = false;
}

//! Adds pair of (simulation, real data) for consecutive simulation
void FitSuite::addSimulationAndRealData(const Simulation& simulation, const OutputData<double >& real_data, const IChiSquaredModule& chi2_module)
{
    m_fit_objects.add(simulation, real_data, chi2_module);
}

//! Adds fit parameter
void FitSuite::addFitParameter(const std::string& name, double value, double step, const AttLimits& attlim, double error)
{
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}

//! Adds fit parameter, step is calculated from initial parameter value
void FitSuite::addFitParameter(const std::string& name, double value, const AttLimits& attlim, double error)
{
    double step = value * getAttributes().getStepFactor();
    m_fit_parameters.addParameter(name, value, step, attlim, error);
}

//! Adds fit strategy
void FitSuite::addFitStrategy(IFitStrategy *strategy)
{
    m_fit_strategies.addStrategy(strategy);
}

void FitSuite::addFitStrategy(const IFitStrategy &strategy)
{
    addFitStrategy(strategy.clone());
}

void FitSuite::setMinimizer(IMinimizer *minimizer)
{
    delete m_minimizer;
    m_minimizer = minimizer;
    if(!m_minimizer) {
        msglog(MSG::WARNING) << "FitSuite::setMinimizer() -> Warning. Attempt to set NULL minimizer.";
    }
}

//! link FitMultiParameters with simulation parameters
void FitSuite::link_fit_parameters()
{
    ParameterPool *pool = m_fit_objects.createParameterTree();
    m_fit_parameters.link_to_pool(pool);
    msglog(MSG::DEBUG2) << "FitSuite::link_fit_parameters() -> Parameter pool:";
    msglog(MSG::DEBUG2) << *pool;
    delete pool;
}

bool FitSuite::check_prerequisites() const
{
    if( !m_minimizer ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No minimizer found.");
    if( !m_fit_objects.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No simulation/data description defined");
    if( !m_fit_parameters.size() ) throw LogicErrorException("FitSuite::check_prerequisites() -> Error! No fit parameters defined");
    return true;
}

void FitSuite::runFit()
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
void FitSuite::minimize()
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
size_t FitSuite::getNCalls() const
{
    //return m_minimizer->getNCalls();
    // I don't know which function Minimizer calls (chi2 or gradient)
    return (m_function_chi2.getNCalls() ? m_function_chi2.getNCalls() : m_function_gradient.getNCalls());
}


// results to stdout
void FitSuite::printResults() const
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
void FitSuite::initPrint(int print_every_nth)
{
    boost::shared_ptr<FitSuitePrintObserver > observer(new FitSuitePrintObserver(print_every_nth));
    attachObserver(observer);
}

FitParameter *FitSuite::getFitParameter(const std::string &name)
{
    return getFitParameters()->getParameter(name);
}

void FitSuite::fixAllParameters()
{
    getFitParameters()->fixAll();
}

void FitSuite::releaseAllParameters()
{
    getFitParameters()->releaseAll();
}

void FitSuite::setParametersFixed(const std::vector<std::string> &pars, bool is_fixed)
{
    getFitParameters()->setParametersFixed(pars, is_fixed);
}

double FitSuite::getRunTime() const
{
    boost::posix_time::time_duration diff = m_end_time - m_start_time;
    return diff.total_milliseconds()/1000.;
}


