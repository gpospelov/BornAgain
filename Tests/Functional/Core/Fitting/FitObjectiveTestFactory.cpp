// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/FitObjectiveTestFactory.cpp
//! @brief     Defines class FitObjectiveTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/Fitting/FitObjectiveTestFactory.h"
#include "Tests/Functional/Core/Fitting/FitObjectiveTestCases.h"

FitObjectiveTestFactory::FitObjectiveTestFactory()
{
    registerItem("MigradCylindersInBA", create_new<MigradCylindersInBA>);
    registerItem("MigradResidualCylindersInBA", create_new<MigradResidualCylindersInBA>);
    registerItem("BfgsCylindersInBA", create_new<BfgsCylindersInBA>);
    registerItem("SteepestDescentCylindersInBA", create_new<SteepestDescentCylindersInBA>);
    registerItem("FumuliCylindersInBA", create_new<FumuliCylindersInBA>);
    registerItem("LevenbergMarquardtCylindersInBA", create_new<LevenbergMarquardtCylindersInBA>);
    registerItem("SimAnCylindersInBA", create_new<SimAnCylindersInBA>);
    registerItem("GeneticCylindersInBA", create_new<GeneticCylindersInBA>);
    registerItem("RectDetectorFit", create_new<RectDetectorFit>);
    registerItem("AdjustMinimizerFit", create_new<AdjustMinimizerFit>);
    registerItem("SpecularFitTest", create_new<SpecularFitTest>);
    registerItem("SpecularFitTestQ", create_new<SpecularFitTestQ>);
    registerItem("MultipleSpecFittingTest", create_new<MultipleSpecFittingTest>);
    registerItem("OffSpecFitTest", create_new<OffSpecFitTest>);
}
