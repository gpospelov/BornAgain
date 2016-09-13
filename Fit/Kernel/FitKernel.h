// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/FitKernel.h
//! @brief     Defines class FitKernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITKERNEL_H
#define FITKERNEL_H

#include "WinDllMacros.h"
#include <memory>
#include <vector>

class FitKernelImp;
class RealLimits;
class Attributes;

//! @class FitKernel
//! @ingroup fitting_internal
//! @brief Main class to setup and run the fitting.

class BA_CORE_API_ FitKernel
{
public:
    typedef std::function<double(const std::vector<double>&)> function_chi2_t;

    FitKernel();
    ~FitKernel();

    //! Sets minimizer with given name and algorithm type
    //! @param minimizerName The name of the minimizer
    //! @param algorithmName Optional name of the minimizer's algorithm
    void setMinimizer(const std::string& minimizerName,
                      const std::string& algorithmName = std::string());

    //! Adds fit parameter
    void addFitParameter(const std::string& name, double value,
                         const RealLimits& lim, const Attributes& attr,
                         double step=0.0);

    void setObjectiveFunction(function_chi2_t func);

    void minimize();

private:
    std::unique_ptr<FitKernelImp> m_impl;
};

#endif
