// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestService.h
//! @brief     Defines class TestService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTSERVICE_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTSERVICE_H

#include "Tests/Functional/TestMachinery/ITestService.h"
#include <boost/format.hpp>
#include <cassert>
#include <iostream>
#include <string>

//! @class TestService
//! @ingroup standard_samples
//! @brief Main class to run standard functional test from standalone executable.
//! Test name is obtained from command line parameters and then constructed via templated factory.

template <typename T> class TestService : public ITestService
{
public:
    TestService() {}

    bool execute(int argc, char** argv)
    {
        assert(argc>1);
        std::string test_name = argv[1];
        assert(!m_test_factory.contains(test_name));

        auto test = m_test_factory.createTest(test_name);
        return test->runTest();
    }

private:
    T m_test_factory;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTSERVICE_H
