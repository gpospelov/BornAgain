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
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "Exceptions.h"
#include "FunctionalTestComponentService.h"
#include "IComponentService.h"
#include "Utils.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include <boost/scoped_ptr.hpp>
#include <iostream>


FunctionalMultiTest::FunctionalMultiTest(const std::string &name, const std::string &description, FunctionalTestComponentService *service)
    : IFunctionalTest(name, description)
    , m_componentService(service)
{

}

FunctionalMultiTest::~FunctionalMultiTest()
{
    delete m_componentService;
    for(std::vector<IFunctionalTest *>::iterator it=m_tests.begin(); it!=m_tests.end(); ++it) {
        delete (*it);
    }
}

void FunctionalMultiTest::runTest()
{
    for(size_t i=0; i<m_componentService->getNumberOfComponents(); ++i) {
        std::cout << "AdvancedFunctionalMultiTest::runTest() -> " << i<< " " << m_name << std::endl;
        m_componentService->setComponent(i);

        IFunctionalTest *test = m_componentService->getFunctionalTest();

        m_test_to_reference_fname[test] = m_componentService->getReferenceFileName();

        test->runTest();
        test->analyseResults();

        m_tests.push_back(test);
    }
}

int FunctionalMultiTest::analyseResults()
{
    for(size_t i=0; i<m_tests.size(); ++i)
        if(m_tests[i]->getTestResult() != SUCCESS) m_result = FAILED;

    if(getTestResult() != SUCCESS)
        saveReferenceDataForFailedTests();

    printResults(std::cout);

    return m_result;
}

void FunctionalMultiTest::printResults(std::ostream &ostr) const
{
    // if single test, use his own printout
    if(m_tests.size() == 1) {
        //m_tests[0]->printResults(ostr);
        ostr << (*m_tests[0]) << "\n";
        return;
    }

    // if multiple test, use fancy print out
    int number_of_failed_tests(0);
    for(size_t i=0; i<m_tests.size(); ++i) {
        if(m_tests[i]->getTestResult() != SUCCESS) ++number_of_failed_tests;
    }

    ostr << getFormattedInfoString();
    ostr << "[" << number_of_failed_tests << " failed out of " << m_tests.size() << "]";
    ostr << "\n";

    for(size_t i=0; i<m_tests.size(); ++i) {
        IFunctionalTest *test = m_tests[i];
        ostr << test->getFormattedInfoString();
//        ostr << Utils::AdjustStringLength(std::string(), width_name)
//             << Utils::AdjustStringLength(test->getName(), width_description)
//             << Utils::AdjustStringLength(test->getTestResultString(), width_result);
//        if(test->getTestResult() == SUCCESS || test->getTestResult() == FAILED_DIFF)
//            ostr << test->getDifference();
//        if(test->getTestResult() != SUCCESS)
//            ostr << "-> saved to " << m_test_to_reference_fname[test];
        ostr << "\n";
    }

}

void FunctionalMultiTest::saveReferenceDataForFailedTests()
{
//    std::string dir_path("00_failed_tests");
//    Utils::FileSystem::CreateDirectory(dir_path);

//    for(size_t i=0; i<m_tests.size(); ++i) {
//        IAdvancedFunctionalTest *test = m_tests[i];
//        if(test->getTestResult() != SUCCESS) {
//            std::string file_name = Utils::FileSystem::GetFileMainName(m_test_to_reference_fname[test]);
//            file_name = Utils::FileSystem::GetJoinPath(dir_path, file_name);
//            m_test_to_reference_fname[test] = file_name;
//            IntensityDataIOFactory::writeIntensityData(*test->getOutputData(), file_name);
//        }
//    }

}


