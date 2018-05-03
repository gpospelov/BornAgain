// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTest.cpp
//! @brief     Implements classes from MinimizerTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerTestCases.h"

MinuitTestV1::MinuitTestV1()
    : MinimizerTest("Minuit2", "Migrad", "RosenbrockPlan") {}

MinuitTestV2::MinuitTestV2()
    : MinimizerTest("Minuit2", "Migrad", "WoodFourPlan") {}

SteepestDescentTestV1::SteepestDescentTestV1()
    : MinimizerTest("GSLMultiMin", "SteepestDescent", "RosenbrockPlan") {}

SteepestDescentTestV2::SteepestDescentTestV2()
    : MinimizerTest("GSLMultiMin", "SteepestDescent", "WoodFourPlan") {}

ConjugateFRTestV1::ConjugateFRTestV1()
    : MinimizerTest("GSLMultiMin", "ConjugateFR", "RosenbrockPlan") {}

ConjugateFRTestV2::ConjugateFRTestV2()
    : MinimizerTest("GSLMultiMin", "ConjugateFR", "WoodFourPlan") {}

ConjugatePRTestV1::ConjugatePRTestV1()
    : MinimizerTest("GSLMultiMin", "ConjugatePR", "RosenbrockPlan") {}

ConjugatePRTestV2::ConjugatePRTestV2()
    : MinimizerTest("GSLMultiMin", "ConjugatePR", "WoodFourPlan") {}

BfgsTestV1::BfgsTestV1()
    : MinimizerTest("GSLMultiMin", "BFGS", "RosenbrockPlan") {}

BfgsTestV2::BfgsTestV2()
    : MinimizerTest("GSLMultiMin", "BFGS", "WoodFourPlan") {}

Bfgs2TestV1::Bfgs2TestV1()
    : MinimizerTest("GSLMultiMin", "BFGS2", "RosenbrockPlan") {}

Bfgs2TestV2::Bfgs2TestV2()
    : MinimizerTest("GSLMultiMin", "BFGS2", "WoodFourPlan") {}
