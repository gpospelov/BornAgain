// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/main.cpp
//! @brief     Implements program to run tests from CoreSpecialTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.h"
#include <cassert>

//! Runs PyEmbedded functional test.
int main(int argc, char** argv)
{
    assert(argc > 1);
    auto test = CoreSpecialTestFactory().createItemPtr(argv[1]);
    return !test->runTest();
}
