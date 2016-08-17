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
#include "Configurable.h"
#include <functional>
#include <vector>

class FitParameter;
class FitSuiteParameters;
class MinimizerOptions;

//! Common interface for all kind minimizers.
//! @ingroup fitting_internal

class BA_CORE_API_ IMinimizer : public Configurable
{
 public:
    //! signature of chi squared function to minimize
    typedef std::function<double(const double*)> function_chi2_t;

    //! signature of gradient to minimize with access to single data element residuals
    typedef std::function<double(const double*, unsigned int, double*)> function_gradient_t;

    IMinimizer() {}
    virtual ~IMinimizer() {}

    //! run minimization
    virtual void minimize() =0;

    //! Sets internal minimizer parameter
//    virtual void setParameter(size_t index, const FitParameter* par) =0;

    //! Sets internal minimizer parameters using external parameter list
    virtual void setParameters(const FitSuiteParameters& parameters) =0;

    //! Sets chi squared function to minimize
    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters) =0;

    //! Sets gradient function to minimize
    virtual void setGradientFunction(
        function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize) =0;

    //! Returns number of variables to fit
    virtual size_t getNumberOfVariables() const =0;

    //! Returns minimum function value
//    virtual double getMinValue() const =0;

    //! Returns values of parameters at the minimum
    virtual std::vector<double> getValueOfVariablesAtMinimum() const =0;

    //! Returns errors of variables at minimum
    virtual std::vector<double> getErrorOfVariables() const =0;

    //! clear resources (parameters) for consecutives minimizations
//    virtual void clear() =0;

    //! Prints fit results
    virtual void printResults() const =0;

    //! Returns number of calls of minimized function
    virtual size_t getNCalls() const { return 0; }

    //! return minimizer options
    virtual MinimizerOptions* getOptions() { return nullptr; }
    virtual const MinimizerOptions* getOptions() const { return nullptr; }

    //! set minimizer options
    virtual void setOptions(const MinimizerOptions&) {}

    //! set minimizer option string
    virtual void setOptionString(const std::string&) {}

    //! Returns true if type of algorithm is Levenberg-Marquardt or similar
    virtual bool isGradientBasedAgorithm() { return false; }

    //! return name of the minimizer
    virtual std::string getMinimizerName() const =0;

    //! return name of the minimization algorithm
    virtual std::string getAlgorithmName() const =0;
};

#endif // IMINIMIZER_H
