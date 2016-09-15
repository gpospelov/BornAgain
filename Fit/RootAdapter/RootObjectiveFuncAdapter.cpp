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
    , m_ndatasize(0)
{

}

void RootObjectiveFunctionAdapter::setFunction(objective_function_t func)
{
    m_objective_function = func;
}

void RootObjectiveFunctionAdapter::setGradientFunction(gradient_function_t func, int ndatasize)
{
    m_gradient_function = func;
    m_ndatasize = ndatasize;
}

void RootObjectiveFunctionAdapter::setNumberOfParameters(int nparameters)
{
    m_nparameters = nparameters;
}

//void RootObjectiveFunctionAdapter::setSizeOfData(int ndatasize)
//{
//    m_ndatasize = ndatasize;
//}

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

    root_objective_t rootfun =
        [&] (const double* pars) {return evaluate(pars); };

    m_root_chi_function.reset(new ROOTMinimizerChiSquaredFunction(rootfun, m_nparameters));

    return m_root_chi_function.get();
}

const ROOTMinimizerGradientFunction *RootObjectiveFunctionAdapter::rootGradientFunction()
{
    if(!m_gradient_function)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootGradientFunction() -> Error. "
                                 "Objective function is not set.");

    if(m_nparameters <= 0)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootGradientFunction() -> Error. "
                                 "Number of parameters must be >0");

    if(m_ndatasize <= 0)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootGradientFunction() -> Error. "
                                 "Number of data elements is not defined.");

    root_gradient_t rootfun =
        [&] (const double *pars, unsigned int index, double *gradients)
        {   return evaluate_gradient(pars, index, gradients); };

    m_root_gradient_function.reset(new ROOTMinimizerGradientFunction(rootfun, m_nparameters, m_ndatasize));

    return m_root_gradient_function.get();
}

double RootObjectiveFunctionAdapter::evaluate(const double *pars)
{
    if(pars == nullptr) {
        std::cout << "RootObjectiveFunctionAdapter::evaluate() -> Error. nullptr" << std::endl;
//        throw std::runtime_error("RootObjectiveFunctionAdapter::evaluate() -> Error. nullptr");
    }

    std::vector<double> vec;
    vec.resize(m_nparameters, 0.0);
    std::copy(pars, pars+m_nparameters, vec.begin());
    return m_objective_function(vec);
}

double RootObjectiveFunctionAdapter::evaluate_gradient(const double *pars, unsigned int index, double *gradients)
{
    std::vector<double> vec;
    vec.resize(m_nparameters, 0.0);
    std::copy(pars, pars+m_nparameters, vec.begin());

    std::vector<double> vec_gradients;

    if(gradients)
        vec_gradients.resize(m_nparameters);

    double result = m_gradient_function(vec, index, vec_gradients);

    if(gradients)
        for(int i=0; i<(int)m_nparameters; ++i) gradients[i] = vec_gradients[i];

    return result;
}

