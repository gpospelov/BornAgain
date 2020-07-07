// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyStandard/PyStandardTest.h
//! @brief     Defines class PyStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_PYTHON_PYSTANDARD_PYSTANDARDTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_PYTHON_PYSTANDARD_PYSTANDARDTEST_H

#include "Tests/Functional/TestMachinery/IStandardTest.h"

//! Tests Python scripts generation from Core objects.
//! Performs core standard simulation and checks it against simulation via generated Python script.

class PyStandardTest : public IStandardTest
{
public:
    using IStandardTest::IStandardTest;

    bool runTest() final;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_PYTHON_PYSTANDARD_PYSTANDARDTEST_H
