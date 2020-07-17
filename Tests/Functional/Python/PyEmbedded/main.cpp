// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/main.cpp
//! @brief     Implements program PyEmbedded to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.h"
#include "Tests/Functional/TestMachinery/TestService.h"

//! Runs PyEmbedded functional test.
int main(int argc, char** argv)
{
    return !TestService<PyEmbeddedTestFactory>().execute(argc, argv);
}
