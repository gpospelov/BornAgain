// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.h
//! @brief     Defines class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMINIMIZER_H
#define IMINIMIZER_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include <string>

class FitParameterSet;

//! @class IMinimizer
//! @ingroup fitting_internal
//! @brief Common interface for all kind minimizer's

class BA_CORE_API_ IMinimizer
{
 public:
    IMinimizer() { }
    virtual ~IMinimizer() { }

    //! return name of the minimizer
    virtual std::string minimizerName() const;

    //! return name of the minimization algorithm
    virtual std::string algorithmName() const;

    //! run minimization
    virtual void minimize();

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear();

    //! Sets internal minimizer parameters using external parameter list
    virtual void setParameters(const FitParameterSet& parameters);

    virtual void setObjectiveFunction(objective_function_t ){}

    virtual void setGradientFunction(gradient_function_t, int ){}

    //! Returns minimum function value
    virtual double getMinValue() const;

    //! Prints fit results
    virtual std::string reportResults() const;

    //! Propagates results of minimization to fit parameter set
    virtual void propagateResults(FitParameterSet& parameters);
};

#endif
