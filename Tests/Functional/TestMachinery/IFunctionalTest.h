// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IFunctionalTest.h
//! @brief     Defines IFunctionalTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IFUNCTIONALTEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IFUNCTIONALTEST_H

#include "Wrap/WinDllMacros.h"
#include <map>
#include <string>

//! Base class for all functional tests.
//! @class IFunctionalTest

class BA_CORE_API_ IFunctionalTest
{
public:
    IFunctionalTest() {}
    virtual ~IFunctionalTest() = default;

    virtual bool runTest() = 0; //!< Returns true when successful
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_IFUNCTIONALTEST_H
