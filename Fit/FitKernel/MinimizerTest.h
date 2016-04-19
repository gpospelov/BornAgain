// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/MinimizerTest.h
//! @brief     Declares class MinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERTEST_H
#define MINIMIZERTEST_H

#include "IMinimizer.h"
#include "FitSuiteParameters.h"
#include <map>


//! @class MinimizerTest
//! @ingroup fitting_internal
//! @brief Minimizer which calls minimization function once to test whole chain

class BA_CORE_API_ MinimizerTest : public IMinimizer
{
 public:
    MinimizerTest() : m_min_value(0) {}
    virtual ~MinimizerTest(){}

    virtual void minimize();

    virtual void setParameters(const FitSuiteParameters& parameters);

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


