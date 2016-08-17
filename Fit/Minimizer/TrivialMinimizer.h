// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TrivialMinimizer.h
//! @brief     Defines class TrivialMinimizer.
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

#include "IMinimizer.h"
#include "FitSuiteParameters.h"

//! @class TrivialMinimizer
//! @ingroup fitting_internal
//! @brief Minimizer which calls minimization function once to test whole chain

class BA_CORE_API_ TrivialMinimizer : public IMinimizer
{
 public:
    TrivialMinimizer() : m_min_value(0) {}
    ~TrivialMinimizer() final {}

    void minimize() final;

    void setParameters(const FitSuiteParameters& parameters) final;

    void setChiSquaredFunction(function_chi2_t fun_chi2, size_t) final { m_fcn = fun_chi2 ; }

    void setGradientFunction(function_gradient_t, size_t, size_t) final {}

    size_t getNumberOfVariables() const final { return m_parameters.size(); }

    std::vector<double> getValueOfVariablesAtMinimum() const final;

    std::vector<double> getErrorOfVariables() const final;

    void printResults() const final;

    std::string getMinimizerName() const final { return "Test"; }
    std::string getAlgorithmName() const final { return ""; }

    MinimizerOptions* getOptions() final { return nullptr; }
    const MinimizerOptions* getOptions() const final { return nullptr; }

 private:
    double m_min_value;
    FitSuiteParameters m_parameters; //! minimizer parameters
    function_chi2_t m_fcn;
};

#endif // TRIVIALMINIMIZER_H
