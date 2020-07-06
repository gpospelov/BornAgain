// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IMinimizerTest.cpp
//! @brief     Defines class MinimizerTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/TestMachinery/IMinimizerTest.h"
#include "Fit/Kernel/Minimizer.h"
#include "Tests/Functional/TestMachinery/MinimizerTestPlan.h"
#include "Fit/Kernel/Parameters.h"
#include <iostream>

using namespace Fit;

IMinimizerTest::IMinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                               const std::string& fit_plan_name)
    : m_minimizer_name(minimizer_name), m_algorithm_name(algorithm_name),
      m_fit_plan_name(fit_plan_name)
{
}

//! Runs minimization and check results of minimization.

bool IMinimizerTest::runTest()
{
    std::cout << "Testing " << m_minimizer_name << "/" << m_algorithm_name << " " << m_fit_plan_name
              << std::endl;

    auto plan = createPlan();

    Minimizer minimizer;
    minimizer.setMinimizer(m_minimizer_name, m_algorithm_name, m_option_string);
    auto success = plan->checkMinimizer(minimizer);

    std::cout << "MinimizerTest::runTest() -> " << (success ? "OK" : "FAILED") << std::endl;
    return success;
}

void IMinimizerTest::setMinimizerOptions(const std::string& options)
{
    m_option_string = options;
}
