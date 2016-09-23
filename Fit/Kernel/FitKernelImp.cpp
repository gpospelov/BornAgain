// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/FitKernelImp.cpp
//! @brief     Declares class FitKernelImp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitKernelImp.h"
#include "IMinimizer.h"
#include "MinimizerUtils.h"
#include <sstream>

FitKernelImp::FitKernelImp()
{

}

FitKernelImp::~FitKernelImp()
{

}

void FitKernelImp::clear()
{
    m_fit_parameters.clear();
    m_minimizer.reset();
}

void FitKernelImp::setMinimizer(IMinimizer *minimizer)
{
    m_minimizer.reset(minimizer);
}

void FitKernelImp::addFitParameter(FitParameter *par)
{
    m_fit_parameters.addFitParameter(par);
}

void FitKernelImp::setObjectiveFunction(objective_function_t func)
{
    m_objective_function.setObjectiveFunction(func);
}

void FitKernelImp::setGradientFunction(gradient_function_t func, int ndatasize)
{
    m_objective_function.setGradientFunction(func, ndatasize);
}

void FitKernelImp::minimize()
{
    if(!m_minimizer)
        throw std::runtime_error("FitKernelImp::minimize() -> Error. Minimizer is not defined.");

    if(m_fit_parameters.size() == 0)
        throw std::runtime_error("FitKernelImp::minimize() -> Error. No fit parameters defined.");

    m_time_interval.start();

    objective_function_t func =
        [&](const std::vector<double> &pars) { return m_objective_function.evaluate(pars); };
    m_minimizer->setObjectiveFunction(func);

    gradient_function_t gradient_func =
        [&](const std::vector<double>& pars, int index, std::vector<double> &gradients)
    {
        return m_objective_function.evaluate_gradient(pars, index, gradients);
    };
    m_minimizer->setGradientFunction(gradient_func, m_objective_function.sizeOfData());

    m_minimizer->setParameters(m_fit_parameters);

    m_minimizer->minimize();

    // set found values to the parameters
    m_minimizer->propagateResults(m_fit_parameters);

    m_time_interval.stop();
}

std::string FitKernelImp::reportResults() const
{
    std::ostringstream result;
    result << std::endl;
    result << MinimizerUtils::sectionString("FitSuite::printResults");
    result << "functionCalls: " << m_objective_function.functionCalls()
           << " (" << m_time_interval.runTime() << " sec total)" << "\n";
    result << m_minimizer->reportResults();
    result << m_fit_parameters.reportResults();
    return result.str();
}

FitParameterSet *FitKernelImp::fitParameters()
{
    return &m_fit_parameters;
}

IMinimizer *FitKernelImp::minimizer()
{
    return m_minimizer.get();
}

int FitKernelImp::functionCalls() const
{
    return m_objective_function.functionCalls();
}
