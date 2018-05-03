// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTestFactory.h
//! @brief     Implements class MinimizerTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerTestFactory.h"
#include "MinimizerTestCases.h"

MinimizerTestFactory::MinimizerTestFactory()
{
    registerItem("MinuitTestV1", create_new<MinuitTestV1>,
                 "Minuit + Migrad + Rosenbrock");
    registerItem("MinuitTestV2", create_new<MinuitTestV2>,
                 "Minuit + Migrad + WoodFour");

    registerItem("SteepestDescentTestV1", create_new<SteepestDescentTestV1>,
                 "GSLMultiMin + SteepestDescent + Rosenbrock");
    registerItem("SteepestDescentTestV2", create_new<SteepestDescentTestV2>,
                 "GSLMultiMin + SteepestDescent + WoodFour");

    registerItem("ConjugateFRTestV1", create_new<ConjugateFRTestV1>,
                 "GSLMultiMin + ConjugateFR + Rosenbrock");
    registerItem("ConjugateFRTestV2", create_new<ConjugateFRTestV2>,
                 "GSLMultiMin + ConjugateFR + WoodFour");

    registerItem("ConjugatePRTestV1", create_new<ConjugatePRTestV1>,
                 "GSLMultiMin + ConjugatePR + Rosenbrock");
    registerItem("ConjugatePRTestV2", create_new<ConjugatePRTestV2>,
                 "GSLMultiMin + ConjugatePR + WoodFour");

    registerItem("BfgsTestV1", create_new<BfgsTestV1>,
                 "GSLMultiMin + BFGS + Rosenbrock");
    registerItem("BfgsTestV2", create_new<BfgsTestV2>,
                 "GSLMultiMin + BFGS + WoodFour");

    registerItem("Bfgs2TestV1", create_new<Bfgs2TestV1>,
                 "GSLMultiMin + BFGS2 + Rosenbrock");
    registerItem("Bfgs2TestV2", create_new<Bfgs2TestV2>,
                 "GSLMultiMin + BFGS2 + WoodFour");

}
