// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalMultiTest.cpp
//! @brief     Implements class FunctionalMultiTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalMultiTest.h"
#include "FunctionalTestComponentService.h"

FunctionalMultiTest::FunctionalMultiTest(const std::string& name,
                                         FunctionalTestComponentService* service)
    : IFunctionalTest(name, service->getTestInfo().m_test_description)
    , m_componentService(service)
{
}

FunctionalMultiTest::~FunctionalMultiTest()
{
    delete m_componentService;
    for (auto it = m_tests.begin(); it != m_tests.end(); ++it)
        delete (*it);
}

void FunctionalMultiTest::runTest()
{
    for (size_t i = 0; i < m_componentService->getNumberOfComponents(); ++i) {
        std::cout << "FunctionalMultiTest::runTest() -> " << getName()
                  << " " << i
                  << "/" << m_componentService->getNumberOfComponents()
                  << " (" << m_componentService->getCurrentComponentName() << ")" << std::endl;

        m_componentService->initComponent(i);

        IFunctionalTest* test = m_componentService->getFunctionalTest();

        test->runTest();
        test->analyseResults();

        m_tests.push_back(test);
    }
}

int FunctionalMultiTest::analyseResults()
{
    for (size_t i = 0; i < m_tests.size(); ++i)
        if (m_tests[i]->getTestResult() != SUCCESS)
            m_result = FAILED;

    printResults(std::cout);

    return m_result;
}

void FunctionalMultiTest::printResults(std::ostream& ostr) const
{
    // if single test, use his own printout
    if (m_tests.size() == 1) {
        ostr << *m_tests[0] << "\n";
        return;
    }

    // if multiple test, use extended print out
    int number_of_failed_tests(0);
    for (size_t i = 0; i < m_tests.size(); ++i) {
        if (m_tests[i]->getTestResult() != SUCCESS)
            ++number_of_failed_tests;
    }

    ostr << getFormattedInfoString();
    ostr << "[" << number_of_failed_tests << " failed out of " << m_tests.size() << "]" << "\n";
    for (size_t i = 0; i < m_tests.size(); ++i)
        ostr << *m_tests[i] << "\n";
}
