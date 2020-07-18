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

MigradCylindersInBA::MigradCylindersInBA()
    : FitObjectiveTest("Minuit2", "Migrad", "CylindersInBAPlan")
{
}

MigradResidualCylindersInBA::MigradResidualCylindersInBA()
    : FitObjectiveTest("Minuit2", "Migrad", "CylindersInBAResidualPlan")
{
}

BfgsCylindersInBA::BfgsCylindersInBA()
    : FitObjectiveTest("GSLMultiMin", "BFGS2", "CylindersInBAEasyPlan")
{
}

SteepestDescentCylindersInBA::SteepestDescentCylindersInBA()
    : FitObjectiveTest("GSLMultiMin", "SteepestDescent", "CylindersInBAEasyPlan")
{
}

FumuliCylindersInBA::FumuliCylindersInBA()
    : FitObjectiveTest("Minuit2", "Fumili", "CylindersInBAResidualPlan")
{
}

LevenbergMarquardtCylindersInBA::LevenbergMarquardtCylindersInBA()
    : FitObjectiveTest("GSLLMA", "", "CylindersInBAResidualPlan")
{
}

SimAnCylindersInBA::SimAnCylindersInBA()
    : FitObjectiveTest("GSLSimAn", "", "CylindersInBAEasyPlan",
                       "IterationsAtTemp=5;MaxIterations=10;t_min=1.0")
{
}

GeneticCylindersInBA::GeneticCylindersInBA()
    : FitObjectiveTest("Genetic", "", "CylindersInBAEasyPlan", "MaxIterations=1;RandomSeed=1")
{
}

RectDetectorFit::RectDetectorFit()
    : FitObjectiveTest("Minuit2", "Migrad", "RectDetPlan", "Strategy=2")
{
}

AdjustMinimizerFit::AdjustMinimizerFit() : FitObjectiveTest("Genetic", "", "AdjustMinimizerPlan") {}

SpecularFitTest::SpecularFitTest() : FitObjectiveTest("Minuit2", "Migrad", "SpecularPlan") {}

SpecularFitTestQ::SpecularFitTestQ() : FitObjectiveTest("Minuit2", "Migrad", "SpecularPlanQ") {}

MultipleSpecFittingTest::MultipleSpecFittingTest()
    : FitObjectiveTest("Minuit2", "Migrad", "MultipleSpecPlan")
{
}

OffSpecFitTest::OffSpecFitTest() : FitObjectiveTest("Minuit2", "Migrad", "OffSpecFitPlan") {}
