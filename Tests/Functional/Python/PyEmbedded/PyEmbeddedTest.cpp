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

#include "PyEmbeddedTest.h"
#include "TestCases.h"
#include <boost/format.hpp>
#include <iostream>

PyEmbeddedTest::PyEmbeddedTest()
{
    m_tests.registerItem("FunctionCall",
                         create_new<FunctionCall>,
                         "Calling function from embedded Python");
    m_tests.registerItem("MethodCall",
                         create_new<MethodCall>,
                         "Creating object embedded and calling its methods.");
}

bool PyEmbeddedTest::execute(int argc, char** argv)
{
    std::string test_name = argc>1 ? std::string(argv[1]) : std::string();

    if (!m_tests.contains(test_name)) {
        for (auto it : m_tests)
            std::cout << boost::format("%-15s | %-50s\n") % it.first % it.second;
        return false;
    }

    auto test = m_tests.createTest(test_name);
    bool result = test->execute();

    std::cout << boost::format("%-15s | %-50s -> %-5s\n") %
                 test->getName() % test->description() %
                 (result ? "OK" : "FAILED");

    return result;
}
