// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/FunctionTestPlanFactory.cpp
//! @brief     Implements class FunctionTestPlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FunctionTestPlanFactory.h"
#include "FunctionTestPlanCases.h"

FunctionTestPlanFactory::FunctionTestPlanFactory()
{
    registerItem("RosenbrockPlan", create_new<RosenbrockPlan>);
    registerItem("EasyRosenbrockPlan", create_new<EasyRosenbrockPlan>);
    registerItem("WoodFourPlan", create_new<WoodFourPlan>);
    registerItem("EasyWoodFourPlan", create_new<EasyWoodFourPlan>);
}
