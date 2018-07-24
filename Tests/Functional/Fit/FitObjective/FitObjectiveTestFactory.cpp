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
                 "Minuit + TwoCylindersInBA");
}
