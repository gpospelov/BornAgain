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

void RootObjectiveFunctionAdapter::setFunction(func_t func, int ndims)
{
    m_ndims = ndims;
    m_func = func;
    IMinimizer::function_chi2_t fun_chi2 =
        [&] (const double* pars) {return evaluate(pars);};

    m_root_chi_function.reset(new ROOTMinimizerChiSquaredFunction(fun_chi2, ndims));
}

double RootObjectiveFunctionAdapter::evaluate(const double *pars)
{
    std::vector<double> vec;
    vec.resize(m_ndims, 0.0);
    std::copy(pars, pars+m_ndims, vec.begin());
    return m_func(vec);
}
