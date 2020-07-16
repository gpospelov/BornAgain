// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestService.h
//! @brief     Defines and implements class TestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTSERVICE_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTSERVICE_H

#include "Wrap/WinDllMacros.h"
#include <cassert>
#include <string>

//! @brief
//! Main class to run standard functional test from standalone executable.
//! Test name is obtained from command line parameters and then constructed via templated factory.
//! @ingroup standard_samples

template <typename T> class BA_CORE_API_ TestService
{
public:
    bool execute(int argc, char** argv)
    {
        assert(argc>1);
        std::string test_name = argv[1];
        assert(test_name!="");
        assert(m_test_factory.contains(test_name));
        auto test = m_test_factory.createTest(test_name);
        assert(test);
        return test->runTest();
    }

private:
    T m_test_factory;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTSERVICE_H
