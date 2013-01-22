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
    MinimizerTest(){}
    virtual ~MinimizerTest(){}

    //! run minimization
    virtual void minimize();

    //! set variable
    virtual void setParameter(size_t index, const FitParameter *par) { m_values[index] = par->getValue(); }

    //! set function to minimize
    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters) { (void)nparameters, m_fcn = fun_chi2; }

    //! get number of variables to fit
    virtual size_t getNumberOfVariables() const { return m_values.size(); }

    //! return pointer to the parameters values at the minimum
    virtual double getValueOfVariableAtMinimum(size_t index) const;

private:
    std::map<int, double > m_values;
    function_chi2_t m_fcn;
};

#endif // MINIMIZERTEST_H

