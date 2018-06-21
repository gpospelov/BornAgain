// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/FunctionTestPlan.h
//! @brief     Defines class FunctionTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FUNCTIONTESTPLAN_H
#define FUNCTIONTESTPLAN_H

#include "KernelTypes.h"
#include "ParameterPlan.h"
#include <memory>
#include <vector>

namespace Fit { class Parameter; class Parameters; class Minimizer;}

//! Defines objective function to fit, expected minimum, initial fit parameters and
//! expected values of fit parameters at minimum.

class FunctionTestPlan
{
public:
    FunctionTestPlan(const std::string &name);

    virtual ~FunctionTestPlan();

    void addParameter(const Fit::Parameter& param, double expected_value, double tolerance = 0.01);

    std::string name() const { return m_name; }

    //! Runs minimization and check minimization result.
    virtual bool checkMinimizer(Fit::Minimizer& minimizer) = 0;

protected:
    Fit::Parameters parameters() const;
    bool valuesAsExpected(const std::vector<double>& values) const;

    std::string m_name; //!< plan name
    std::vector<ParameterPlan> m_parameter_plan; //! initial/expected parameter values
};


class ScalarTestPlan : public FunctionTestPlan
{
public:
    ScalarTestPlan(const std::string &name, scalar_function_t func, double expected_minimum,
                   double tolerance = 0.01);

    bool checkMinimizer(Fit::Minimizer& minimizer);

private:
    fcn_scalar_t scalarFunction() const;
    bool minimumAsExpected(double found_minimum, double tolerance = 0.01) const;

    scalar_function_t m_objective_function; //!< objective function to minimize
    double m_expected_minimum; //!< expected function minimum
    //!< Tolerance on found minimum of objective function wrt expected.
    double m_tolerance_on_minimum;
};

class ResidualTestPlan : public FunctionTestPlan
{
public:
    using test_funct_t = std::function<double(double, const std::vector<double>&)>;

    ResidualTestPlan(const std::string &name, test_funct_t func);
    ~ResidualTestPlan();

    fcn_residual_t residualFunction();

    bool checkMinimizer(Fit::Minimizer& minimizer);

private:
    void init_data_values();

    std::vector<double> evaluate(const std::vector<double>& pars);
    std::vector<double> m_xvalues;
    std::vector<double> m_data_values;
    test_funct_t m_test_func;
};

#endif // OBJECTIVEFUNCTIONPLAN_H
