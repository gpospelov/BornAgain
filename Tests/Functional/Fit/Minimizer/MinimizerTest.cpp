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
//! Returns true if minimization result is consistent with expectancies.
bool checkResult(const Fit::MinimizerResult& result, const FunctionTestPlan& plan);
}

using namespace Fit;

MinimizerTest::MinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                             const std::string& fit_plan_name)
    : m_minimizer_name(minimizer_name), m_algorithm_name(algorithm_name),
      m_fit_plan_name(fit_plan_name)
{
}

bool MinimizerTest::runTest()
{
    bool success(true);

    std::cout << "Testing " << m_minimizer_name << "/" << m_algorithm_name << " " << m_fit_plan_name
              << std::endl;

    FunctionTestPlanFactory plan_factory;
    auto plan = plan_factory.create(m_fit_plan_name);

    Minimizer minimizer;
    minimizer.setMinimizer(m_minimizer_name, m_algorithm_name);
    auto result = minimizer.minimize(plan->objectiveFunction(), plan->parameters());

    std::cout << result.toString() << std::endl;

    success = checkResult(result, *plan);

    std::cout << "MinimizerTest::runTest() -> " << (success ? "OK" : "FAILED") << std::endl;
    return success;
}

namespace {
bool checkResult(const Fit::MinimizerResult& result, const FunctionTestPlan& plan)
{
    bool success(true);
    std::cout << "MinimizerTest::checkResult() -> " << plan.name() << std::endl;

    success &= plan.valuesAsExpected(result.parameters().values());
    success &= plan.minimumAsExpected(result.minValue());

    std::cout << std::endl;

    return success;
}
}
