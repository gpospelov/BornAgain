// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTest.h
//! @brief     Defines class MinimizerTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerTest.h"
#include "FunctionTestPlan.h"
#include "FunctionTestPlanFactory.h"
#include "KernelTypes.h"
#include "Minimizer.h"
#include "ObjectiveTestFunctions.h"
#include "Parameters.h"
#include <iostream>

namespace {
const double default_tolerance_on_function_min = 0.01;
}

using namespace Fit;

MinimizerTest::MinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                             const std::string& fit_plan_name)
    : m_minimizer_name(minimizer_name), m_algorithm_name(algorithm_name),
      m_fit_plan_name(fit_plan_name), m_tolerance(default_tolerance_on_function_min)
{
}

//! Runs minimization and check results of minimization.

bool MinimizerTest::runTest()
{
    bool success(true);

    std::cout << "Testing " << m_minimizer_name << "/" << m_algorithm_name << " " << m_fit_plan_name
              << std::endl;

    auto plan = createPlan();

    Minimizer minimizer;
    minimizer.setMinimizer(m_minimizer_name, m_algorithm_name);
    auto result = minimizer.minimize(plan->scalarFunction(), plan->parameters());

    std::cout << result.toString() << std::endl;

    success = checkResult(result, *plan);

    std::cout << "MinimizerTest::runTest() -> " << (success ? "OK" : "FAILED") << std::endl;
    return success;
}

std::unique_ptr<FunctionTestPlan> MinimizerTest::createPlan() const
{
    FunctionTestPlanFactory plan_factory;
    return plan_factory.create(m_fit_plan_name);
}

//! Returns true if minimization result is consistent with expectancies.

bool MinimizerTest::checkResult(const MinimizerResult& result, const FunctionTestPlan& plan)
{
    bool success(true);
    std::cout << "MinimizerTest::checkResult() -> " << plan.name() << std::endl;

    success &= plan.valuesAsExpected(result.parameters().values());
    success &= plan.minimumAsExpected(result.minValue(), m_tolerance);

    std::cout << std::endl;

    return success;
}
