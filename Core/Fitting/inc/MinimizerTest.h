#ifndef MINIMIZERTEST_H
#define MINIMIZERTEST_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MinimizerTest.h
//! @brief  Definition of MinimizerTest class
//! @author Scientific Computing Group at FRM II
//! @date   21.01.2013

#include "IMinimizer.h"
#include "FitSuiteParameters.h"
#include <map>


//- -------------------------------------------------------------------
//! @class MinimizerTest
//! @brief Minimizer which calls minimization function once to test whole chain
//- -------------------------------------------------------------------
class MinimizerTest : public IMinimizer
{
public:
    MinimizerTest() : m_min_value(0) {}
    virtual ~MinimizerTest(){}

    virtual void minimize();

    virtual void setParameters(const FitSuiteParameters &parameters);

    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters) { (void)nparameters, m_fcn = fun_chi2; }

    virtual void setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)
    {
        (void)fun_gradient;
        (void)nparameters;
        (void)ndatasize;
    }

    virtual size_t getNumberOfVariables() const { return m_parameters.size(); }

    virtual double getValueOfVariableAtMinimum(size_t index) const;

    virtual std::vector<double > getValueOfVariablesAtMinimum() const;

    virtual void printResults() const;

private:
    double m_min_value;
    FitSuiteParameters m_parameters; //! minimizer parameters
    function_chi2_t m_fcn;
};

#endif // MINIMIZERTEST_H

