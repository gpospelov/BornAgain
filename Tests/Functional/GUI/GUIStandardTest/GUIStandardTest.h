// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/GUIStandardTest.h
//! @brief     Defines class GUIStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUISTANDARDTEST_H
#define GUISTANDARDTEST_H

#include "IStandardTest.h"

//! A functional test of the BornAgain GUI.
//! Performs a given standard simulation directly, and through domain->GUI->domain,
//! and compares results.

class GUIStandardTest : public IStandardTest
{
public:
    using IStandardTest::IStandardTest;

    bool runTest() final;
};

#endif // GUISTANDARDTEST_H
