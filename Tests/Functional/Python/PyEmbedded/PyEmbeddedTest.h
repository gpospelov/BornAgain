// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedTest.cpp
//! @brief     Implements PyEmbeddedTest to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYEMBEDDEDTEST_H
#define PYEMBEDDEDTEST_H

#include <string>
#include "FunctionalTestFactory.h"

class FunctionalTestFactory;

//! @class PyEmbeddedTest
//! @brief Tests various aspects of running embedded Python in C++ program.

class PyEmbeddedTest
{
public:
    PyEmbeddedTest();

    bool execute(int argc, char** argv);

private:
    FunctionalTestFactory m_tests;
};

#endif
