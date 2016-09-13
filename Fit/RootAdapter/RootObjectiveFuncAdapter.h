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
#include <memory>
#include <vector>

class ROOTMinimizerChiSquaredFunction;

//! @class RootObjectiveFunctionAdapter
//! @ingroup fitting_internal
//! @brief The RootObjectiveFunctionAdapter class adapts our objective functions to ROOT.

class BA_CORE_API_ RootObjectiveFunctionAdapter
{
public:
    typedef std::function<double(const std::vector<double>&)> func_t;

    void setFunction(func_t func, int ndims);


    const ROOTMinimizerChiSquaredFunction  *rootChiSquaredFunction() const { return m_root_chi_function.get(); }

private:
    double evaluate(const double *pars);

    func_t m_func;

    std::unique_ptr<ROOTMinimizerChiSquaredFunction> m_root_chi_function;
    int m_ndims;
};

#endif
