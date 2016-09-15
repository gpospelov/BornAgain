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
#include <sstream>

FitKernelImp::FitKernelImp()
{

}

FitKernelImp::~FitKernelImp()
{

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
    objective_function_t func =
        [&](const std::vector<double> &pars) { return m_objective_function.evaluate(pars); };
    m_minimizer->setObjectiveFunction(func);

    gradient_function_t gradient_func =
        [&](const std::vector<double>& pars, int index, std::vector<double> &gradients)
    {
        return m_objective_function.evaluate_gradient(pars, index, gradients);
    };
    m_minimizer->setGradientFunctionNew(gradient_func, m_objective_function.sizeOfData());

    m_minimizer->setParameters(m_fit_parameters);

    // minimize
    try {
        m_minimizer->minimize();
    } catch (int) {}

    // set found values to the parameters
    m_minimizer->propagateResults(m_fit_parameters);
}

std::string FitKernelImp::reportResults() const
{
    std::ostringstream result;

     result << std::endl;
     result
         << "--- FitSuite::printResults -----------------------------------------------------\n";
     result << "functionCalls: " << m_objective_function.functionCalls() << "\n";
//     result << " Chi2:" << std::scientific << std::setprecision(8)
//               << m_fit_objects.getChiSquaredValue()
//               << "    chi2.NCall:" << m_function_chi2.getNCalls()
//               << "  grad.NCall:" << m_function_gradient.getNCalls() << ","
//               << m_function_gradient.getNCallsGradient() << ","
//               << m_function_gradient.getNCallsTotal() << " (neval, ngrad, total)" << std::endl;

     result << m_minimizer->reportResults();
     result << m_fit_parameters.reportResults();

     return result.str();
}

FitSuiteParameters *FitKernelImp::fitParameters()
{
    return &m_fit_parameters;
}

IMinimizer *FitKernelImp::minimizer()
{
    return m_minimizer.get();
}
