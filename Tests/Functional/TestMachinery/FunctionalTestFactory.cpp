// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/FunctionalTestFactory.cpp
//! @brief     Defines FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/TestMachinery/FunctionalTestFactory.h"

std::unique_ptr<IFunctionalTest> FunctionalTestFactory::createTest(std::string& test_name)
{
    return createItemPtr(test_name);
}
