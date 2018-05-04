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

//! Setting for standalone fit of rosenbrock function.

class RosenbrockPlan : public FunctionTestPlan
{
public:
    RosenbrockPlan();
};

//! Setting for standalone fit of WoodFour function.

class WoodFourPlan : public FunctionTestPlan
{
public:
    WoodFourPlan();
};

#endif  //  FUNCTIONTESTPLANCASES_H

