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
#include "ObjectiveTestFunctions.h"
#include "ParameterPlan.h"
#include "Parameters.h"

using namespace Fit;

FunctionTestPlan::FunctionTestPlan(const std::string& name, fcn_scalar_t func,
                                   double expected_minimum)
    : m_name(name), m_objective_function(func), m_expected_minimum(expected_minimum)
{
}

FunctionTestPlan::~FunctionTestPlan() = default;

void FunctionTestPlan::addPlan(const Parameter& param, double expected_value, double tolerance)
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

//! Plan to minimmize a Rosenbrock function.

RosenbrockPlan::RosenbrockPlan() : FunctionTestPlan("Rosenbrock1", TestFunctions::RosenBrock, 0.0)
{
    addPlan(Parameter("par1", -1.2, AttLimits::limited(-5.0, 5.0), 0.01), 1.0);
    addPlan(Parameter("par2", 1.0, AttLimits::limited(-5.0, 5.0), 0.01), 1.0);
}
