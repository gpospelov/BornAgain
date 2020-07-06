// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/GUIStandardTest.h
//! @brief     Defines class GUIStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISTANDARDTEST_GUISTANDARDTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISTANDARDTEST_GUISTANDARDTEST_H

#include "Tests/Functional/TestMachinery/IStandardTest.h"

//! A functional test of the BornAgain GUI.
//! Performs a given standard simulation directly, and through domain->GUI->domain,
//! and compares results.

class GUIStandardTest : public IStandardTest
{
public:
    using IStandardTest::IStandardTest;

    bool runTest() final;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISTANDARDTEST_GUISTANDARDTEST_H
