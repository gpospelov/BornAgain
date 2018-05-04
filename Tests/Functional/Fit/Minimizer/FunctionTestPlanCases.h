// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/FunctionTestPlanCases.h
//! @brief     Defines collection of FunctionTestPlan classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FUNCTIONTESTPLANCASES_H
#define FUNCTIONTESTPLANCASES_H

#include "FunctionTestPlan.h"

//! Setting for standalone fit of Rosenbrock function.

class RosenbrockPlan : public ScalarTestPlan
{
public:
    RosenbrockPlan();
};

//! Setting for standalone fit of Rosenbrock function. Fit parameter limits
//! are made small here to help stochastic minimizer to converge in reasonable time.

class EasyRosenbrockPlan : public ScalarTestPlan
{
public:
    EasyRosenbrockPlan();
};

//! Setting for standalone fit of WoodFour function.

class WoodFourPlan : public ScalarTestPlan
{
public:
    WoodFourPlan();
};

//! Setting for standalone fit of WoodFour function. Fit parameter limits
//! are made small here to help stochastic minimizer to converge in reasonable time.

class EasyWoodFourPlan : public ScalarTestPlan
{
public:
    EasyWoodFourPlan();
};

#endif  //  FUNCTIONTESTPLANCASES_H

