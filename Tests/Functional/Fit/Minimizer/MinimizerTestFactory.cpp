// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTestFactory.cpp
//! @brief     Implements class MinimizerTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Fit/Minimizer/MinimizerTestFactory.h"
#include "Tests/Functional/Fit/Minimizer/MinimizerTestCases.h"

MinimizerTestFactory::MinimizerTestFactory()
{
    registerItem("MinuitTestV1", create_new<MinuitTestV1>);
    registerItem("MinuitTestV2", create_new<MinuitTestV2>);
    registerItem("MinuitTestV3", create_new<MinuitTestV3>);

    registerItem("SteepestDescentTestV1", create_new<SteepestDescentTestV1>);
    registerItem("SteepestDescentTestV2", create_new<SteepestDescentTestV2>);

    registerItem("ConjugateFRTestV1", create_new<ConjugateFRTestV1>);
    registerItem("ConjugateFRTestV2", create_new<ConjugateFRTestV2>);

    registerItem("ConjugatePRTestV1", create_new<ConjugatePRTestV1>);
    registerItem("ConjugatePRTestV2", create_new<ConjugatePRTestV2>);

    registerItem("BfgsTestV1", create_new<BfgsTestV1>);
    registerItem("BfgsTestV2", create_new<BfgsTestV2>);

    registerItem("Bfgs2TestV1", create_new<Bfgs2TestV1>);
    registerItem("Bfgs2TestV2", create_new<Bfgs2TestV2>);

    registerItem("GSLSimAnTestV1", create_new<GSLSimAnTestV1>);
    registerItem("GSLSimAnTestV2", create_new<GSLSimAnTestV2>);

    registerItem("GeneticTestV1", create_new<GeneticTestV1>);
    registerItem("GeneticTestV2", create_new<GeneticTestV2>);

    registerItem("FumiliTestV3", create_new<FumiliTestV3>);

    registerItem("LevenbergMarquardtV3", create_new<LevenbergMarquardtV3>);

    registerItem("TestMinimizerV1", create_new<TestMinimizerV1>);
}
