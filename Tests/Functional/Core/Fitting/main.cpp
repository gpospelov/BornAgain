// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/main.cpp
//! @brief     Implements program FitTest to run fit functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/Fitting/FitObjectiveTestFactory.h"
#include "Tests/Functional/TestMachinery/TestService.h"

//! Runs functional tests.

int main(int argc, char** argv)
{
    return TestService<FitObjectiveTestFactory>().execute(argc, argv) ? 0 : 1;
}
