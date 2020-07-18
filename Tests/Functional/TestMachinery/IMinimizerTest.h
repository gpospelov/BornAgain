// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IMinimizerTest.h
//! @brief     Defines class MinimizerTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IMINIMIZERTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IMINIMIZERTEST_H

#include "Tests/Functional/TestMachinery/IFunctionalTest.h"
#include <memory>
#include <string>

class MinimizerTestPlan;

//! Base class for minimizer tests.

class BA_CORE_API_ IMinimizerTest : public IFunctionalTest
{
public:
    IMinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                   const std::string& fit_plan_name, const std::string& options = "");

    bool runTest();

protected:
    virtual std::unique_ptr<MinimizerTestPlan> createPlan() const = 0;

    const std::string m_minimizer_name;
    const std::string m_algorithm_name;
    const std::string m_fit_plan_name;
    const std::string m_option_string;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IMINIMIZERTEST_H
