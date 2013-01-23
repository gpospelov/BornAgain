#ifndef IMINIMIZER_H
#define IMINIMIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IMinimizer.h
//! @brief  Definition of Minimizer class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012

#include <boost/function.hpp>
#include "Exceptions.h"

class FitParameter;
class FitSuiteParameters;


//- -------------------------------------------------------------------
//! @class IMinimizer
//! @brief Common interface for all kind minimizer's
//- -------------------------------------------------------------------
class IMinimizer
{
public:
    //! signature of chi squared function to minimize
    typedef boost::function<double(const double *)> function_chi2_t;

    //! signature of gradient to minimize with acess to single data element residuals
    typedef boost::function<double(const double *, unsigned int, double *)> function_gradient_t;

    IMinimizer() { }
    virtual ~IMinimizer() { }

    //! run minimization
    virtual void minimize() = 0;

    //! set internal minimizer parameter
    virtual void setParameter(size_t index, const FitParameter *par);

    //! set internal minimizer parameters using external parameter list
    virtual void setParameters(const FitSuiteParameters &parameters);

    //! set chi squared function to minimize
    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters);

    //! set gradient function to minimize
    virtual void setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize);

    //! get number of variables to fit
    virtual size_t getNumberOfVariables() const;

    //! return minimum function value
    virtual double getMinValue() const;

    //! return pointer to the parameters values at the minimum
    virtual double getValueOfVariableAtMinimum(size_t i) const;

    //! return pointer to the parameters values at the minimum
    virtual double getErrorOfVariable(size_t i) const;

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear();

    //! print fit results
    virtual void printResults() const;

    //! set minimizer command
    virtual void setOptions(const std::string &option);
};


inline void IMinimizer::setParameter(size_t index, const FitParameter *par)
{
    (void)index;
    (void)par;
    throw NotImplementedException("IMinimizer::setParameter() -> Not implemented.");
}

inline void IMinimizer::setParameters(const FitSuiteParameters &parameters)
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

inline void IMinimizer::setOptions(const std::string &options)
{
    (void)options;
    throw NotImplementedException("IMinimizer::setOptions() -> Not implemented.");
}

#endif // IMINIMIZER_H
