// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteImp.cpp
//! @brief     Implements class FitSuiteImp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteImp.h"
#include "RealLimits.h"
#include "FitParameter.h"
#include "FitParameterLinked.h"
#include "Logger.h"
#include "MinimizerFactory.h"
#include "ParameterPool.h"
#include "IMinimizer.h"
#include "FitKernel.h"
#include <stdexcept>

FitSuiteImp::FitSuiteImp(const std::function<void()>& notifyObservers)
//    : m_minimizer(MinimizerFactory::createMinimizer("Minuit2", "Migrad"))
    : m_is_last_iteration(false)
    , m_is_interrupted(false)
    , m_notifyObservers(notifyObservers)
    , m_kernel(new FitKernel)
{
    m_function_chi2.init(this);
    m_function_gradient.init(this);
    m_fit_strategies.init(this);
}

FitSuiteImp::~FitSuiteImp()
{
    clear();
}

//! Clears all data.
void FitSuiteImp::clear()
{
    m_fit_objects.clear();
//    m_fit_parameters.clear();
    m_fit_strategies.clear();
    m_is_last_iteration = false;
    m_is_interrupted = false;
}

//! Adds pair of (simulation, real data) for consecutive simulation
void FitSuiteImp::addSimulationAndRealData(const GISASSimulation& simulation,
                                         const OutputData<double>& real_data, double weight)
{
    m_fit_objects.add(simulation, real_data, weight);
}

//! Adds fit parameter, step is calculated from initial parameter value
FitParameterLinked *FitSuiteImp::addFitParameter(const std::string& name, double value,
                                  const AttLimits& limits, double step)
{
    if(step <=0.0)
        step = value * getOptions().getStepFactor();

    FitParameterLinked *result = new FitParameterLinked(name, value, limits, step);
    m_kernel->fitParameters()->addFitParameter(result);
    return result;
}

void FitSuiteImp::addFitStrategy(const IFitStrategy& strategy)
{
    m_fit_strategies.addStrategy(strategy.clone());
}

void FitSuiteImp::setMinimizer(IMinimizer* minimizer)
{
    if(!minimizer)
        throw std::runtime_error(
            "FitSuite::setMinimizer() -> Error. Attempt to set nullptr minimizer");
//    m_minimizer.reset(minimizer);
    m_kernel->setMinimizer(minimizer);
}

void FitSuiteImp::runFit()
{
    m_start_time = boost::posix_time::microsec_clock::local_time();

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

void FitSuiteImp::minimize()
{
    // initialize minimizer with fitting functions
//    IMinimizer::function_chi2_t fun_chi2 =
//        [&] (const double* pars) {return m_function_chi2.evaluate(pars);};
//    m_minimizer->setChiSquaredFunction( fun_chi2, m_fit_parameters.size());

    objective_function_t fun_chi2 =
        [&] (const std::vector<double>& pars) {return m_function_chi2.evaluate(pars);};
    m_kernel->setObjectiveFunction( fun_chi2);

    gradient_function_t fun_gradient =
        [&] (const std::vector<double>& pars, int index, std::vector<double> &gradients)
        {
            return m_function_gradient.evaluate(pars, index, gradients);
        };
    m_kernel->setGradientFunction(
        fun_gradient, m_fit_objects.getSizeOfDataSet() );

    // initialize minimizer's parameters with the list of local fit parameters
//    m_minimizer->setParameters(m_fit_parameters);

    // setting number of free parameters for proper chi2 normalization
//    m_fit_objects.setNfreeParameters((int)m_fit_parameters.numberOfFreeFitParameters());
    m_fit_objects.setNfreeParameters((int)getFitParameters()->freeFitParameterCount());

    // minimize
    try {
//        m_minimizer->minimize();
        m_kernel->minimize();
    } catch (int) {}

    // set found values to the parameters
//    m_minimizer->propagateResults(m_fit_parameters);

    m_fit_objects.runSimulations(); // we run simulation once again for best values found
}

FitParameterSet *FitSuiteImp::getFitParameters() {
//    return &m_fit_parameters;
    return m_kernel->fitParameters();
}

// get current number of minimization function calls
size_t FitSuiteImp::getNCalls() const
{
    //return m_minimizer->getNCalls();
    // I don't know which function Minimizer calls (chi2 or gradient)
    return m_function_chi2.getNCalls() ?
        m_function_chi2.getNCalls() : m_function_gradient.getNCalls();
}

size_t FitSuiteImp::getCurrentStrategyIndex() const
{
    return m_fit_strategies.getCurrentStrategyIndex();
}

std::string FitSuiteImp::reportResults() const
{
//    std::ostringstream result;

//     result << std::endl;
//     result
//         << "--- FitSuite::printResults -----------------------------------------------------\n";
//     result << " Chi2:" << std::scientific << std::setprecision(8)
//               << m_fit_objects.getChiSquaredValue()
//               << "    chi2.NCall:" << m_function_chi2.getNCalls()
//               << "  grad.NCall:" << m_function_gradient.getNCalls() << ","
//               << m_function_gradient.getNCallsGradient() << ","
//               << m_function_gradient.getNCallsTotal() << " (neval, ngrad, total)" << std::endl;

//     result << m_minimizer->reportResults();
//     result << m_fit_parameters.reportResults();

//     return result.str();
    return m_kernel->reportResults();
}

double FitSuiteImp::getRunTime() const
{
    boost::posix_time::time_duration diff = m_end_time - m_start_time;
    return diff.total_milliseconds()/1000.;
}

const FitKernel *FitSuiteImp::kernel() const
{
   return m_kernel.get();
}

//FitKernel *FitSuiteImp::kernel()
//{
//   return m_kernel.get();
//}

bool FitSuiteImp::check_prerequisites() const
{
//    if( !m_minimizer ) throw Exceptions::LogicErrorException(
//        "FitSuite::check_prerequisites() -> Error! No minimizer found.");
    if( !m_fit_objects.getNumberOfFitObjects() ) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No simulation/data description defined");
//    if( !m_fit_parameters.size() ) throw Exceptions::LogicErrorException(
//        "FitSuite::check_prerequisites() -> Error! No fit parameters defined");
    if( m_fit_objects.getSizeOfDataSet() == 0) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No elements to fit. "
        "Looks like whole detector is masked.");
    return true;
}

//! link FitMultiParameters with simulation parameters
void FitSuiteImp::link_fit_parameters()
{
    const std::unique_ptr<ParameterPool> pool(m_fit_objects.createParameterTree());
    for (auto par: *m_kernel->fitParameters()) {
        FitParameterLinked* linkedPar = dynamic_cast<FitParameterLinked*>(par);
        if( !linkedPar )
            throw std::runtime_error(
                "FitKernel::link_fit_parameters() -> Error! Can't cast to FitParameterLinked.");
        linkedPar->addMatchedParametersFromPool(pool.get());
    }
    msglog(MSG::DEBUG2) << "FitSuite::link_fit_parameters() -> Parameter pool:";
    msglog(MSG::DEBUG2) << *pool;
}

//void FitSuiteKernel::link_fit_parameters()
//{
//    const std::unique_ptr<ParameterPool> pool(m_fit_objects.createParameterTree());
//    for (auto par: m_fit_parameters.getFitParameters()) {
//        FitParameterLinked* linkedPar = dynamic_cast<FitParameterLinked*>(par);
//        if( !linkedPar )
//            throw std::runtime_error(
//                "FitKernel::link_fit_parameters() -> Error! Can't cast to FitParameterLinked.");
//        linkedPar->addMatchedParametersFromPool(pool.get());
//    }
//    msglog(MSG::DEBUG2) << "FitSuite::link_fit_parameters() -> Parameter pool:";
//    msglog(MSG::DEBUG2) << *pool;
//}
