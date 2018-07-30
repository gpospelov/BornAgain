// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitObjectiveTestFactory.h
//! @brief     Defines class FitObjectiveTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjectiveTestFactory.h"
#include "FitObjectiveTestCases.h"

FitObjectiveTestFactory::FitObjectiveTestFactory()
{
    registerItem("MigradCylindersInBA", create_new<MigradCylindersInBA>,
                 "Minuit + CylindersInBA");
    registerItem("BfgsCylindersInBA", create_new<BfgsCylindersInBA>,
                 "BFGS + CylindersInBA");
    registerItem("SteepestDescentCylindersInBA", create_new<SteepestDescentCylindersInBA>,
                 "SteepestDescent + CylindersInBA");
    registerItem("FumuliCylindersInBA", create_new<FumuliCylindersInBA>,
                 "Fumili + CylindersInBA (Residual)");
    registerItem("LevenbergMarquardtCylindersInBA", create_new<LevenbergMarquardtCylindersInBA>,
                 "Levenberg-Marquardt + CylindersInBA (Residual)");
    registerItem("SimAnCylindersInBA", create_new<SimAnCylindersInBA>,
                 "Simulated annealing + CylindersInBA (Easy)");
    registerItem("GeneticCylindersInBA", create_new<GeneticCylindersInBA>,
                 "Genetic + CylindersInBA (Easy)");
    registerItem("RectDetectorFit", create_new<RectDetectorFit>,
                 "Minuit + RectDet with ROI, CylindersInBA");
    registerItem("AdjustMinimizerFit", create_new<AdjustMinimizerFit>,
                 "Minuit + Genetic, CylindersInBA");
    registerItem("MultiPatternFit", create_new<MultiPatternFit>,
                 "Minuit, MultiPatternSample");
    registerItem("SpecularNewFitTest", create_new<SpecularNewFitTest>,
                 "Minuit, Basic specular fitting");
}
