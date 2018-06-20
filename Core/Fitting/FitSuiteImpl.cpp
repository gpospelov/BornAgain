// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteImpl.cpp
//! @brief     Implements class FitSuiteImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitSuiteImpl.h"
#include "RealLimits.h"
#include "FitParameter.h"
#include "MinimizerFactory.h"
#include "ParameterPool.h"
#include "IMinimizer.h"
#include "FitSuiteUtils.h"
#include "Minimizer.h"
#include "MinimizerConstants.h"
#include <stdexcept>


FitSuiteImpl::FitSuiteImpl(const std::function<void()>& notifyObservers)
    : m_is_last_iteration(false)
    , m_is_interrupted(false)
    , m_notifyObservers(notifyObservers)
    , m_new_kernel(new Fit::Minimizer)
    , m_iteration_count(0)
    , m_is_gradient_based(false)
{
    m_fit_strategies.init(this);
}

FitSuiteImpl::~FitSuiteImpl()
{
    clear();
}

//! Clears all data.
void FitSuiteImpl::clear()
{
    m_fit_objects.clear();
    m_fit_strategies.clear();
    m_is_last_iteration = false;
    m_is_interrupted = false;
}

//! Adds pair of (simulation, real data) for consecutive simulation
FitObject* FitSuiteImpl::addSimulationAndRealData(const Simulation& simulation,
                                         const OutputData<double>& real_data, double weight)
{
    return m_fit_objects.add(simulation, real_data, weight);
}

//! Adds fit parameter, step is calculated from initial parameter value
FitParameter* FitSuiteImpl::addFitParameter(const std::string& pattern, double value,
                                  const AttLimits& limits, double step)
{
    if(step <=0.0)
        step = value * getOptions().stepFactor();

    FitParameter* result = new FitParameter(pattern, value, limits, step);
    fitParameters()->addFitParameter(result);
    return result;
}

FitParameter* FitSuiteImpl::addFitParameter(const FitParameter& fitPar)
{
    FitParameter* result = fitPar.clone();
    if(result->step() <= 0.0)
        result->setStep(result->value() * getOptions().stepFactor());

    fitParameters()->addFitParameter(result);
    return result;
}

void FitSuiteImpl::addFitStrategy(const IFitStrategy& strategy)
{
    m_fit_strategies.addStrategy(strategy);
}

void FitSuiteImpl::setMinimizer(IMinimizer* minimizer)
{
    if (minimizer->algorithmName() == AlgorithmNames::Fumili)
        m_is_gradient_based = true;

    if (minimizer->minimizerName() == MinimizerNames::GSLLMA)
        m_is_gradient_based = true;

    m_new_kernel->setMinimizer(minimizer);
}

void FitSuiteImpl::runFit()
{
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
}

void FitSuiteImpl::minimize()
{
    fcn_scalar_t scalar_fcn =
        [&] (const Fit::Parameters& pars) {return scalar_func_new_kernel(pars);};

    fcn_residual_t residual_fcn =
            [&] (const Fit::Parameters& pars) {return residual_func_new_kernel(pars);};

    m_fit_objects.setNfreeParameters((int)fitParameters()->freeFitParameterCount());

    Fit::Parameters pars = fitParameters()->fitParametersNewKernel();

    if (m_is_gradient_based)
        m_minimizerResult = m_new_kernel->minimize(residual_fcn, pars);
    else
        m_minimizerResult = m_new_kernel->minimize(scalar_fcn, pars);

    m_fit_parameters.setValues(m_minimizerResult.parameters().values());
}


FitParameterSet* FitSuiteImpl::fitParameters() {
    return &m_fit_parameters;
}

// get current number of minimization function calls
size_t FitSuiteImpl::numberOfIterations() const
{
    return m_iteration_count;
}

size_t FitSuiteImpl::currentStrategyIndex() const
{
    return m_fit_strategies.currentStrategyIndex();
}

std::string FitSuiteImpl::reportResults() const
{
    return m_minimizerResult.toString();
}

// method is not const because we have to link fit parameters with the sample,
// to know what is going to be fitted
std::string FitSuiteImpl::setupToString()
{
    check_prerequisites();
    link_fit_parameters();
    std::stringstream result;
    result << FitSuiteUtils::fitParameterSettingsToString(*fitParameters());
    return result.str();
}

bool FitSuiteImpl::check_prerequisites() const
{
    if( !m_fit_objects.size() ) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No simulation/data description defined");
    if( m_fit_objects.getSizeOfDataSet() == 0) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No elements to fit. "
        "Looks like whole detector is masked.");
    return true;
}

//! link FitMultiParameters with simulation parameters
void FitSuiteImpl::link_fit_parameters()
{
    std::unique_ptr<ParameterPool> pool(m_fit_objects.createParameterTree());
    auto parameters = FitSuiteUtils::linkedParameters(*fitParameters());

    if(parameters.empty())
        throw Exceptions::RuntimeErrorException("No fit Parameters defined.");

    for (auto par: parameters)
        par->addMatchedParameters(*pool);

    if(FitSuiteUtils::hasConflicts(*fitParameters())) {
        std::ostringstream message;
        message << "FitSuite::runFit() -> Error. Fit parameters are conflicting with each other, "
                << "meaning that one sample parameter can be controlled by "
                << "two different fit parameters.\n";
        message << FitSuiteUtils::fitParameterSettingsToString(*fitParameters());
        throw Exceptions::RuntimeErrorException(message.str());
    }

}

//! Refactoring temp: new minimizer's objective functions.

double FitSuiteImpl::scalar_func_new_kernel(const Fit::Parameters& fit_pars)
{
    if (isInterrupted())
        throw std::runtime_error("Fitting was interrupted by the user.");

    ++m_iteration_count;
    fitParameters()->setValues(fit_pars.values());
    fitObjects()->runSimulations();
    double chi_squared = fitObjects()->getChiSquaredValue();
    notifyObservers();
    return chi_squared;
}

std::vector<double> FitSuiteImpl::residual_func_new_kernel(const Fit::Parameters& fit_pars)
{
    if (isInterrupted())
        throw std::runtime_error("Fitting was interrupted by the user.");

    ++m_iteration_count;

    fitParameters()->setValues(fit_pars.values());
    fitObjects()->runSimulations();
    notifyObservers();

    return fitObjects()->residuals();
}
