// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreStandardTest/main.cpp
//! @brief     Implements program CoreStandardTest to run core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/CoreStandardTest/CoreStandardTest.h"
#include "Tests/Functional/TestMachinery/StandardTestService.h"

//! Runs CoreStandardTest on a standard simulation indicated by argv[1].

int main(int argc, char** argv)
{
    return !StandardTestService<CoreStandardTest>().execute(argc, argv);
}
