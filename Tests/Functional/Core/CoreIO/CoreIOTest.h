// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreIO/CoreIOTest.h
//! @brief     Defines CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COREIOTEST_H
#define COREIOTEST_H

#include "IFunctionalTest.h"

//! Functional test to validate read/write of large data files.

class CoreIOTest : public IFunctionalTest
{
public:
    CoreIOTest() {}
    ~CoreIOTest() {}

    bool runTest();
};

#endif // COREIOTEST_H
