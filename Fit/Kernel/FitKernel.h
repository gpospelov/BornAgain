// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/FitKernel.h
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
#include "KernelTypes.h"
#include <memory>
#include <string>

class FitKernelImpl;
class AttLimits;
class FitParameterSet;
class IMinimizer;

//! @class FitKernel
//! @ingroup fitting_internal
//! @brief Main class to setup and run the minimization.

class BA_CORE_API_ FitKernel
{
public:
    FitKernel();
    ~FitKernel();

    void clear();

    //! Sets minimizer with given name and algorithm type
    //! @param minimizerName The name of the minimizer
    //! @param algorithmName Optional name of the minimizer's algorithm
    void setMinimizer(const std::string& minimizerName,
                      const std::string& algorithmName = std::string());

    void setMinimizer(IMinimizer* minimizer);

    //! Returns minimizer.
    const IMinimizer *minimizer() const;

    //! Adds fit parameter
    void addFitParameter(const std::string& name, double value,
                         const AttLimits& limits, double step);

    void setObjectiveFunction(objective_function_t func);

    void setGradientFunction(gradient_function_t func, int ndatasize);

    void minimize();

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    FitParameterSet* fitParameters();
    const FitParameterSet* fitParameters() const;

    //! Number of objective function calls.
    int functionCalls() const;
private:
    std::unique_ptr<FitKernelImpl> m_impl;
};

#endif // FITKERNEL_H
