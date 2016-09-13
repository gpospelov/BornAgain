// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/FitKernelImp.h
//! @brief     Defines class FitKernelImp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITKERNELIMP_H
#define FITKERNELIMP_H

#include "WinDllMacros.h"
#include "FitSuiteParameters.h"
#include <memory>

class IMinimizer;
class FitParameter;

//! @class FitKernelImp
//! @ingroup fitting_internal
//! @brief The FitKernel implementation.

class BA_CORE_API_ FitKernelImp
{
public:
    typedef std::function<double(const std::vector<double>&)> function_chi2_t;

    FitKernelImp();
    ~FitKernelImp();

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Adds fit parameter
    void addFitParameter(FitParameter* par);

    void setObjectiveFunction(function_chi2_t func);

    void minimize();

private:
    FitSuiteParameters m_fit_parameters;
    std::unique_ptr<IMinimizer> m_minimizer;
    function_chi2_t m_chi2_func;
};

#endif
