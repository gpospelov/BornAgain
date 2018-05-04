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

FunctionTestPlan::FunctionTestPlan(const std::string& name, fcn_scalar_t func,
                                   double expected_minimum)
    : m_name(name), m_objective_function(func), m_expected_minimum(expected_minimum)
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

//! Returns true if found minimum of objective function coincide with expected.

bool FunctionTestPlan::minimumAsExpected(double found_minimum,  double tolerance) const
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
