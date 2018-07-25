// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitObjectiveTestCases.h
//! @brief     Defines classes from FitObjectiveTest family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjectiveTestCases.h"

MigradCylindersInBA::MigradCylindersInBA()
    : FitObjectiveTest("Minuit2", "Migrad", "CylindersInBAPlan") {}

BfgsCylindersInBA::BfgsCylindersInBA()
    : FitObjectiveTest("GSLMultiMin", "BFGS", "CylindersInBAPlan") {}

SteepestDescentCylindersInBA::SteepestDescentCylindersInBA()
    : FitObjectiveTest("GSLMultiMin", "SteepestDescent", "CylindersInBAPlan") {}

FumuliCylindersInBA::FumuliCylindersInBA()
    : FitObjectiveTest("Minuit2", "Fumili", "CylindersInBAResidualPlan") {}

