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

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_MINIMIZERTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_MINIMIZERTEST_H

#include "Tests/Functional/TestMachinery/IMinimizerTest.h"

//! Collection of standalone tests for fitting library.

class MinimizerTest : public IMinimizerTest
{
public:
    MinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                  const std::string& fit_plan_name, const std::string& options = "");

protected:
    std::unique_ptr<MinimizerTestPlan> createPlan() const;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_MINIMIZERTEST_H
