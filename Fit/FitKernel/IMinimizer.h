// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/IMinimizer.h
//! @brief     Declares class IMinimizer.
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
#include "Macros.h"
#include <functional>
#include "Exceptions.h"
#include <vector>
#include "MinimizerOptions.h"

class FitParameter;
class FitSuiteParameters;


//! @class IMinimizer
//! @ingroup fitting_internal
//! @brief Common interface for all kind minimizer's

class BA_CORE_API_ IMinimizer
{
 public:
    //! signature of chi squared function to minimize
    typedef std::function<double(const double *)> function_chi2_t;

    //! signature of gradient to minimize with access to single data element residuals
    typedef std::function<double(const double *, unsigned int, double *)> function_gradient_t;

    IMinimizer() { }
    virtual ~IMinimizer() { }

    //! run minimization
    virtual void minimize();

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

    //! Returns error of variable at minimum
    virtual double getErrorOfVariable(size_t index) const;

    //! Returns errors of variables at minimum
    virtual std::vector<double >  getErrorOfVariables() const;

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear();

    //! Prints fit results
    virtual void printResults() const;

    //! Returns number of calls of minimized function
    virtual size_t getNCalls() const;

    //! return minimizer options
    virtual MinimizerOptions *getOptions();
    virtual const MinimizerOptions *getOptions() const;

    //! set minimizer options
    virtual void setOptions(const MinimizerOptions &options);

    //! set minimizer option string
    virtual void setOptionString(const std::string& options);

    //! Returns true if type of algorithm is Levenberg-Marquardt or similar
    virtual bool isGradientBasedAgorithm();

    //! return name of the minimizer
    virtual std::string getMinimizerName() const;

    //! return name of the minimization algorithm
    virtual std::string getAlgorithmName() const;

};

inline void IMinimizer::minimize()
{
    throw Exceptions::NotImplementedException("IMinimizer::minimize() -> Not implemented.");
}

inline void IMinimizer::setParameter(size_t /*index*/, const FitParameter* /*par*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setParameter() -> Not implemented.");
}

inline void IMinimizer::setParameters(const FitSuiteParameters& /*parameters*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setParameters() -> Not implemented.");
}

inline void IMinimizer::setChiSquaredFunction(function_chi2_t /*fun_chi2*/, size_t /*nparameters*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setChiSquaredFunction() -> Not implemented.");
}

inline void IMinimizer::setGradientFunction(function_gradient_t /*fun_gradient*/, size_t /*nparameters*/, size_t /*ndatasize*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setGradientFunction() -> Not implemented.");
}

inline size_t IMinimizer::getNumberOfVariables() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getNumberOfVariables() -> Not implemented.");
}

inline double IMinimizer::getMinValue() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getMinValue() -> Not implemented.");
}

inline double IMinimizer::getValueOfVariableAtMinimum(size_t /*index*/) const
{
    throw Exceptions::NotImplementedException("IMinimizer::getValueOfVariableAtMinimum() -> Not implemented.");
}

inline std::vector<double > IMinimizer::getValueOfVariablesAtMinimum() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getValueOfVariablesAtMinimum() -> Not implemented.");
}

inline double IMinimizer::getErrorOfVariable(size_t /*index*/) const
{
    throw Exceptions::NotImplementedException("IMinimizer::getErrorOfVariable() -> Not implemented.");
}

inline std::vector<double> IMinimizer::getErrorOfVariables() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getErrorOfVariables() -> Not implemented.");
}

inline void IMinimizer::clear()
{
    throw Exceptions::NotImplementedException("IMinimizer::clear() -> Not implemented.");
}

inline void IMinimizer::printResults() const
{
    throw Exceptions::NotImplementedException("IMinimizer::printResults() -> Not implemented.");
}

inline size_t IMinimizer::getNCalls() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getNCalls() -> Not implemented.");
}

inline MinimizerOptions *IMinimizer::getOptions()
{
    throw Exceptions::NotImplementedException("IMinimizer::getOptions() -> Not implemented.");
}


inline const MinimizerOptions *IMinimizer::getOptions() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getOptions() -> Not implemented.");
}

inline void IMinimizer::setOptions(const MinimizerOptions &/*options*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setOptions() -> Not implemented.");
}

inline void IMinimizer::setOptionString(const std::string &/*options*/)
{
    throw Exceptions::NotImplementedException("IMinimizer::setOptionString() -> Not implemented.");
}

inline bool IMinimizer::isGradientBasedAgorithm()
{
    throw Exceptions::NotImplementedException("IMinimizer::isGradientBasedAlgorithm() -> Not implemented.");
}

inline std::string IMinimizer::getMinimizerName() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getMinimizerName() -> Not implemented.");
}

inline std::string IMinimizer::getAlgorithmName() const
{
    throw Exceptions::NotImplementedException("IMinimizer::getAlgorithmName() -> Not implemented.");
}



#endif // IMINIMIZER_H


