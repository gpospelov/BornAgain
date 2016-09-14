// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/RootObjectiveFunctionAdapter.h
//! @brief     Implements class RootObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RootObjectiveFuncAdapter.h"
#include "ROOTMinimizerFunction.h"
#include "IMinimizer.h"
#include <stdexcept>

RootObjectiveFunctionAdapter::RootObjectiveFunctionAdapter()
    : m_nparameters(0)
{

}

void RootObjectiveFunctionAdapter::setFunction(objective_function_t func)
{
    m_objective_function = func;
}

void RootObjectiveFunctionAdapter::setNumberOfParameters(int nparameters)
{
    m_nparameters = nparameters;
}

//! Creates objective function suitable for ROOT minimizers.

const ROOTMinimizerChiSquaredFunction*
    RootObjectiveFunctionAdapter::rootChiSquaredFunction()
{
    if(!m_objective_function)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootChiSquaredFunction() -> Error. "
                                 "Objective function is not set.");

    if(m_nparameters <= 0)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootChiSquaredFunction() -> Error. "
                                 "Number of parameters must be >0");

    root_evaluate_t fun_chi2 =
        [&] (const double* pars) {return evaluate(pars);};

    m_root_chi_function.reset(new ROOTMinimizerChiSquaredFunction(fun_chi2, m_nparameters));

    return m_root_chi_function.get();
}

double RootObjectiveFunctionAdapter::evaluate(const double *pars)
{
    std::vector<double> vec;
    vec.resize(m_nparameters, 0.0);
    std::copy(pars, pars+m_nparameters, vec.begin());
    return m_objective_function(vec);
}
