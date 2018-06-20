// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/FitKernelImpl.cpp
//! @brief     Declares class FitKernelImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitKernelImpl.h"
#include "IMinimizer.h"
#include "MinimizerResultsHelper.h"
#include "MinimizerUtils.h"
#include <sstream>

FitKernelImpl::FitKernelImpl(FitParameterSet* fit_parameter_set)
    : m_fit_parameters(fit_parameter_set){}

FitKernelImpl::~FitKernelImpl() {}

void FitKernelImpl::clear()
{
    fitParameters()->clear();
    m_minimizer.reset();
}

void FitKernelImpl::setMinimizer(IMinimizer* minimizer)
{
    m_minimizer.reset(minimizer);
}

void FitKernelImpl::addFitParameter(IFitParameter* par)
{
    fitParameters()->addFitParameter(par);
}

void FitKernelImpl::setObjectiveFunction(objective_function_t func)
{
    m_objective_function.setObjectiveFunction(func);
}

void FitKernelImpl::setGradientFunction(gradient_function_t func, int ndatasize)
{
    m_objective_function.setGradientFunction(func, ndatasize);
}

void FitKernelImpl::minimize()
{
    if(!m_minimizer)
        throw std::runtime_error("FitKernelImpl::minimize() -> Error. Minimizer is not defined.");

    if(fitParameters()->size() == 0)
        return;

    m_time_interval.start();

    objective_function_t func =
        [&](const std::vector<double> &pars) { return m_objective_function.evaluate(pars); };
    m_minimizer->setObjectiveFunction(func);

    gradient_function_t gradient_func =
        [&](const std::vector<double>& pars, int index, std::vector<double>& gradients)
    {
        return m_objective_function.evaluate_gradient(pars, index, gradients);
    };
    m_minimizer->setGradientFunction(gradient_func, m_objective_function.sizeOfData());

    m_minimizer->setParameters(*fitParameters());

    m_minimizer->minimize();

    // set found values to the parameters
    m_minimizer->propagateResults(*fitParameters());

    m_time_interval.stop();
}

std::string FitKernelImpl::reportResults() const
{
    std::ostringstream result;
    result << std::endl;
    result << MinimizerUtils::sectionString("FitSuite::printResults");
    result << "functionCalls: " << m_objective_function.functionCalls()
           << " (" << m_time_interval.runTime() << " sec total)" << "\n";
    result << m_minimizer->reportOutcome();
    result << MinimizerResultsHelper().reportParameters(fitParameters());
    return result.str();
}

FitParameterSet* FitKernelImpl::fitParameters()
{
    return m_fit_parameters;
}

const FitParameterSet*FitKernelImpl::fitParameters() const
{
    return m_fit_parameters;
}

IMinimizer* FitKernelImpl::minimizer()
{
    return m_minimizer.get();
}

int FitKernelImpl::functionCalls() const
{
    return m_objective_function.functionCalls();
}
