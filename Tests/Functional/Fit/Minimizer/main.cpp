// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/main.cpp
//! @brief     Implements program FitTest to run fit functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Fit/Minimizer/MinimizerTestFactory.h"
#include <cassert>

//! Runs functional tests.

int main(int argc, char** argv)
{
    assert(argc > 1);
    auto test = MinimizerTestFactory().createItemPtr(argv[1]);
    return !test->runTest();
}
