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

//! @class RootObjectiveFunctionAdapter
//! @ingroup fitting_internal
//! @brief The RootObjectiveFunctionAdapter class adapts our objective functions to ROOT.

class BA_CORE_API_ RootObjectiveFunctionAdapter
{
public:
    typedef std::function<double(const double*)> root_evaluate_t;

    RootObjectiveFunctionAdapter();

    void setFunction(objective_function_t func);

    void setNumberOfParameters(int nparameters);

    const ROOTMinimizerChiSquaredFunction* rootChiSquaredFunction();

private:
    double evaluate(const double *pars);

    objective_function_t m_objective_function;

    std::unique_ptr<ROOTMinimizerChiSquaredFunction> m_root_chi_function;
    int m_nparameters;
};

#endif
