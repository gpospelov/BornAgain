// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/inc/IMinimizer.h
//! @brief     Defines class IMinimizer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMINIMIZER_H
#define IMINIMIZER_H

#include "WinDllMacros.h"

#include "Macros.h"
GCC_DIAG_OFF(unused-local-typedefs);
#include <boost/function.hpp>
GCC_DIAG_ON(unused-local-typedefs);


#include "Exceptions.h"
#include <vector>

class FitParameter;
class FitSuiteParameters;

//! Common interface for all kind minimizer's

class BA_CORE_API_ IMinimizer
{
 public:
    //! signature of chi squared function to minimize
    typedef boost::function<double(const double *)> function_chi2_t;

    //! signature of gradient to minimize with access to single data element residuals
    typedef boost::function<double(const double *, unsigned int, double *)> function_gradient_t;

    IMinimizer() { }
    virtual ~IMinimizer() { }

    //! run minimization
    virtual void minimize() = 0;

    //! Sets internal minimizer parameter
    virtual void setParameter(size_t index, const FitParameter *par);

    //! Sets internal minimizer parameters using external parameter list
    virtual void setParameters(const FitSuiteParameters& parameters);

    //! Sets chi squared function to minimize
    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters);

    //! Sets gradient function to minimize
    virtual void setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize);

    //! Returns number of variables to fit
    virtual size_t getNumberOfVariables() const;

    //! Returns minimum function value
    virtual double getMinValue() const;

    //! Returns value of the parameter at the minimum
    virtual double getValueOfVariableAtMinimum(size_t index) const;

    //! Returns values of parameters at the minimum
    virtual std::vector<double > getValueOfVariablesAtMinimum() const;

    //! Returns pointer to the parameters values at the minimum
    virtual double getErrorOfVariable(size_t index) const;

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear();

    //! Prints fit results
    virtual void printResults() const;

    //! Sets minimizer option
    virtual void setOptions(const std::string& option);

    //! Returns number of calls of minimized function
    virtual size_t getNCalls() const;
};

inline void IMinimizer::setParameter(size_t index, const FitParameter *par)
{
    (void)index;
    (void)par;
    throw NotImplementedException("IMinimizer::setParameter() -> Not implemented.");
}

inline void IMinimizer::setParameters(const FitSuiteParameters& parameters)
{
    (void)parameters;
    throw NotImplementedException("IMinimizer::setParameters() -> Not implemented.");
}

inline void IMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)
{
    (void)fun_chi2;
    (void)nparameters;
    throw NotImplementedException("IMinimizer::setChiSquaredFunction() -> Not implemented.");
}

inline void IMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)
{
    (void)fun_gradient;
    (void)nparameters;
    (void)ndatasize;
    throw NotImplementedException("IMinimizer::setGradientFunction() -> Not implemented.");
}

inline size_t IMinimizer::getNumberOfVariables() const
{
    throw NotImplementedException("IMinimizer::getNumberOfVariables() -> Not implemented.");
}

inline double IMinimizer::getMinValue() const
{
    throw NotImplementedException("IMinimizer::getMinValue() -> Not implemented.");
}

inline double IMinimizer::getValueOfVariableAtMinimum(size_t index) const
{
    (void)index;
    throw NotImplementedException("IMinimizer::getValueOfVariableAtMinimum() -> Not implemented.");
}

inline std::vector<double > IMinimizer::getValueOfVariablesAtMinimum() const
{
    throw NotImplementedException("IMinimizer::getValueOfVariablesAtMinimum() -> Not implemented.");
}

inline double IMinimizer::getErrorOfVariable(size_t index) const
{
    (void)index;
    throw NotImplementedException("IMinimizer::getErrorOfVariable() -> Not implemented.");
}

inline void IMinimizer::clear()
{
    throw NotImplementedException("IMinimizer::clear() -> Not implemented.");
}

inline void IMinimizer::printResults() const
{
    throw NotImplementedException("IMinimizer::printResults() -> Not implemented.");
}

inline void IMinimizer::setOptions(const std::string& options)
{
    (void)options;
    throw NotImplementedException("IMinimizer::setOptions() -> Not implemented.");
}

inline size_t IMinimizer::getNCalls() const
{
    throw NotImplementedException("IMinimizer::getNCalls() -> Not implemented.");
}

#endif // IMINIMIZER_H


