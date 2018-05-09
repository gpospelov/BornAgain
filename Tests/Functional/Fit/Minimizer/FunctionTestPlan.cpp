// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/FunctionTestPlan.h
//! @brief     Implements class FunctionTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FunctionTestPlan.h"
#include "ParameterPlan.h"
#include "Parameters.h"
#include "Numeric.h"
#include "FixedBinAxis.h"
#include "Minimizer.h"
#include <cmath>
#include <iostream>
#include <sstream>

namespace {
double get_difference(double a, double b)
{
    return std::abs(a-b);
}

}

using namespace Fit;

FunctionTestPlan::FunctionTestPlan(const std::string& name)
    : m_name(name)
{
}

FunctionTestPlan::~FunctionTestPlan() = default;

void FunctionTestPlan::addParameter(const Parameter& param, double expected_value, double tolerance)
{
    m_parameter_plan.push_back(ParameterPlan(param, expected_value, tolerance));
}

//! Returns fit parameters which will be used as initial one for the minimization.

Parameters FunctionTestPlan::parameters() const
{
    Parameters result;
    for (const auto& plan : m_parameter_plan)
        result.add(plan.fitParameter());

    return result;
}

//! Returns true if given values coincide with expected fit parameter values.

bool FunctionTestPlan::valuesAsExpected(const std::vector<double>& values) const
{
    bool success(true);

    if (m_parameter_plan.size() != values.size())
        throw std::runtime_error("FunctionTestPlan::valuesAsExpected() -> Error. Sizes differ.");

    size_t index(0);
    std::ostringstream text;
    for (const auto& plan : m_parameter_plan) {
        double diff = get_difference(values[index], plan.expectedValue());
        if (diff > plan.tolerance())
            success = false;

        text << plan.fitParameter().name()
             << " found:" << values[index]
             << " expected:" << plan.expectedValue()
             << " diff:" << diff << " "
             << (success ? "OK" : "FAILED")
             << "\n";

        ++index;
    }

    std::cout << text.str();

    return success;
}

// ------------------------------------------------------------------------------------------------

ScalarTestPlan::ScalarTestPlan(const std::string& name, objective_function_t func,
                               double expected_minimum, double tolerance)
    : FunctionTestPlan(name)
    , m_objective_function(func)
    , m_expected_minimum(expected_minimum)
    , m_tolerance_on_minimum(tolerance)
{

}

//! Returns true if found minimum of objective function coincide with expected.

bool ScalarTestPlan::minimumAsExpected(double found_minimum,  double tolerance) const
{
    bool success(true);

    double diff = get_difference(found_minimum, m_expected_minimum);
    if (diff > tolerance)
        success = false;

    std::ostringstream text;
    text << "Found minimum:" << found_minimum << " Expected minimum:" << m_expected_minimum
         << " diff:" << diff << " " << (success ? "OK" : "FAILED");
    std::cout << text.str() << std::endl;

    return success;
}

bool ScalarTestPlan::checkMinimizer(Minimizer& minimizer)
{
    bool success(true);

    auto result = minimizer.minimize(scalarFunction(), parameters());
    std::cout << result.toString() << std::endl;

    std::cout << "ScalarTestPlan::checkResult() -> " << name() << std::endl;

    success &= valuesAsExpected(result.parameters().values());
    success &= minimumAsExpected(result.minValue(), m_tolerance_on_minimum);
    std::cout << std::endl;

    return success;
}

fcn_scalar_t ScalarTestPlan::scalarFunction() const
{
    fcn_scalar_t func = [&](const Parameters& params) {
       return m_objective_function(params.values());
    };
    return func;
}

// ------------------------------------------------------------------------------------------------

ResidualTestPlan::ResidualTestPlan(const std::string& name, test_funct_t func)
    : FunctionTestPlan(name)
    , m_test_func(func)
{
    FixedBinAxis axis("x", 100, 0.0, 10.0);
    m_xvalues = axis.getBinBoundaries();

}

ResidualTestPlan::~ResidualTestPlan() = default;

fcn_residual_t ResidualTestPlan::residualFunction()
{
    fcn_residual_t func =
        [&](const std::vector<double>& pars) -> std::vector<double>
    {
        return evaluate(pars);
    };

    return func;
}

bool ResidualTestPlan::checkMinimizer(Minimizer& minimizer)
{
    bool success(true);

    auto result = minimizer.minimize(residualFunction(), parameters());
    std::cout << result.toString() << std::endl;

    std::cout << "ScalarTestPlan::checkResult() -> " << name() << std::endl;
    success &= valuesAsExpected(result.parameters().values());
    std::cout << std::endl;

    return success;
}

void ResidualTestPlan::init_data_values()
{
    std::vector<double> pars;
    for (const auto& plan : m_parameter_plan)
        pars.push_back(plan.expectedValue());

    for(auto x : m_xvalues)
        m_data_values.push_back(m_test_func(x, pars));
}


std::vector<double> ResidualTestPlan::evaluate(const std::vector<double>& pars)
{
    if (m_data_values.empty())
        init_data_values();

    std::vector<double> result;

    size_t index(0);
    for(auto x : m_xvalues) {
        result.push_back(m_test_func(x, pars) - m_data_values[index]);
        ++index;
    }

    return result;
}

