// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/RootObjectiveFunctionAdapter.h
//! @brief     Declares class RootObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROOTOBJECTIVEFUNCTIONADAPTER_H
#define ROOTOBJECTIVEFUNCTIONADAPTER_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include <memory>
#include <vector>

class ROOTMinimizerChiSquaredFunction;
class ROOTMinimizerGradientFunction;

//! @class RootObjectiveFunctionAdapter
//! @ingroup fitting_internal
//! @brief The RootObjectiveFunctionAdapter class adapts our objective functions to ROOT.

class BA_CORE_API_ RootObjectiveFunctionAdapter
{
public:
    typedef std::function<double(const double*)> root_objective_t;
    typedef std::function<double(const double*, unsigned int, double*)> root_gradient_t;

    RootObjectiveFunctionAdapter();

    void setFunction(objective_function_t func);
    void setGradientFunction(gradient_function_t func, int ndatasize);

    void setNumberOfParameters(int nparameters);

//    void setSizeOfData(int ndatasize);

    const ROOTMinimizerChiSquaredFunction* rootChiSquaredFunction();

    const ROOTMinimizerGradientFunction *rootGradientFunction();

private:
    double evaluate(const double *pars);
    double evaluate_gradient(const double *pars, unsigned int index, double *gradients);

    objective_function_t m_objective_function;
    gradient_function_t m_gradient_function;

    std::unique_ptr<ROOTMinimizerChiSquaredFunction> m_root_chi_function;
    std::unique_ptr<ROOTMinimizerGradientFunction> m_root_gradient_function;

    int m_nparameters;
    int m_ndatasize;
};

#endif
