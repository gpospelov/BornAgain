// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyStandardTest.h
//! @brief     Defines class PyStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSTANDARDTEST_H
#define PYSTANDARDTEST_H

#include "IStandardTest.h"

//! A functional test of PyCore (the Python wrapper of BornAgain/Core).
//! Performs a given standard simulation, both directly and from a Python dump.

class PyStandardTest : public IStandardTest
{
public:
    using IStandardTest::IStandardTest;

    bool runTest() final;
};

#endif // PYSTANDARDTEST_H
