// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TrivialMinimizer.h
//! @brief     Declares class TrivialMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRIVIALMINIMIZER_H
#define TRIVIALMINIMIZER_H

#include "IMinimizer.h" // inheriting from
#include "FitSuiteParameters.h"

//! @class TrivialMinimizer
//! @ingroup fitting_internal
//! @brief Minimizer which calls minimization function once to test whole chain

class BA_CORE_API_ TrivialMinimizer : public IMinimizer
{
 public:
    TrivialMinimizer() : m_min_value(0) {}
    virtual ~TrivialMinimizer(){}

    virtual void minimize();

    virtual void setParameters(const FitSuiteParameters& parameters);

    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t) { m_fcn = fun_chi2; }

    virtual void setGradientFunction(function_gradient_t, size_t, size_t) {}

    virtual size_t getNumberOfVariables() const { return m_parameters.size(); }

    virtual double getValueOfVariableAtMinimum(size_t index) const;

    virtual std::vector<double > getValueOfVariablesAtMinimum() const;

    virtual void printResults() const;

    virtual std::vector<double >  getErrorOfVariables() const;

    virtual std::string getMinimizerName() const;

    virtual std::string getAlgorithmName() const;

    virtual MinimizerOptions *getOptions();
    virtual const MinimizerOptions *getOptions() const;

 private:
    double m_min_value;
    FitSuiteParameters m_parameters; //! minimizer parameters
    function_chi2_t m_fcn;
};

#endif // TRIVIALMINIMIZER_H
