// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/FitObjectiveTestCases.cpp
//! @brief     Defines classes from FitObjectiveTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/Fitting/FitObjectiveTestCases.h"

TEST_F(CoreFitting, MigradCylindersInBA)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "CylindersInBAPlan"));
}

TEST_F(CoreFitting, MigradResidualCylindersInBA)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "CylindersInBAResidualPlan"));
}

TEST_F(CoreFitting, BfgsCylindersInBA)
{
    EXPECT_TRUE(run("GSLMultiMin", "BFGS2", "CylindersInBAEasyPlan"));
}

TEST_F(CoreFitting, SteepestDescentCylindersInBA)
{
    EXPECT_TRUE(run("GSLMultiMin", "SteepestDescent", "CylindersInBAEasyPlan"));
}

TEST_F(CoreFitting, FumuliCylindersInBA)
{
    EXPECT_TRUE(run("Minuit2", "Fumili", "CylindersInBAResidualPlan"));
}

TEST_F(CoreFitting, LevenbergMarquardtCylindersInBA)
{
    EXPECT_TRUE(run("GSLLMA", "", "CylindersInBAResidualPlan"));
}

TEST_F(CoreFitting, SimAnCylindersInBA)
{
    EXPECT_TRUE(run("GSLSimAn", "", "CylindersInBAEasyPlan",
                       "IterationsAtTemp=5;MaxIterations=10;t_min=1.0"));
}

TEST_F(CoreFitting, GeneticCylindersInBA)
{
    EXPECT_TRUE(run("Genetic", "", "CylindersInBAEasyPlan", "MaxIterations=1;RandomSeed=1"));
}

TEST_F(CoreFitting, RectDetectorFit)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "RectDetPlan", "Strategy=2"));
}

TEST_F(CoreFitting, AdjustMinimizerFit)
{
    EXPECT_TRUE(run("Genetic", "", "AdjustMinimizerPlan"));
}

TEST_F(CoreFitting, SpecularFitTest)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "SpecularPlan"));
}

TEST_F(CoreFitting, SpecularFitTestQ)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "SpecularPlanQ"));
}

TEST_F(CoreFitting, MultipleSpecFittingTest)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "MultipleSpecPlan"));
}

TEST_F(CoreFitting, OffSpecFitTest)
{
    EXPECT_TRUE(run("Minuit2", "Migrad", "OffSpecFitPlan"));
}
