// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.cpp
//! @brief     Implements class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AdvancedFunctionalTest.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "Exceptions.h"
#include "FunctionalTestComponentService.h"
#include "IComponentService.h"
#include "Utils.h"
#include <boost/scoped_ptr.hpp>
#include <iostream>

AdvancedFunctionalTest::AdvancedFunctionalTest(const std::string &name, GISASSimulation *simulation, OutputData<double> *reference, double threshold)
    : m_name(name)
    , m_simulation(simulation)
    , m_reference(reference)
    , m_threshold(threshold)
{

}

AdvancedFunctionalTest::~AdvancedFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}

void AdvancedFunctionalTest::runTest()
{
    if(!m_simulation) {
        throw NullPointerException("AdvancedFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }
    m_simulation->runSimulation();
}

int AdvancedFunctionalTest::analyseResults()
{
    if(!m_reference)  return FAILED;

    double diff = IntensityDataFunctions::getRelativeDifference(*m_simulation->getOutputData(),*m_reference);

    std::cout << m_name << " " << diff
              << " " << (diff>m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > m_threshold ) return FAILED;
    return SUCCESS;
}

// -------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------

AdvancedFunctionalMultiTest::AdvancedFunctionalMultiTest(const std::string &name, FunctionalTestComponentService *service)
    : m_name(name)
    , m_componentService(service)
{

}

AdvancedFunctionalMultiTest::~AdvancedFunctionalMultiTest()
{
    delete m_componentService;
    for(std::vector<IAdvancedFunctionalTest *>::iterator it=m_tests.begin(); it!=m_tests.end(); ++it) {
        delete (*it);
    }
}

void AdvancedFunctionalMultiTest::runTest()
{
    for(size_t i=0; i<m_componentService->getNumberOfComponents(); ++i) {
        std::cout << "AdvancedFunctionalMultiTest::runTest() -> " << i<< std::endl;
        m_componentService->setComponent(i);

        AdvancedFunctionalTest *test = new AdvancedFunctionalTest(
            m_name, m_componentService->getSimulation(), m_componentService->getReferenceData(),
            m_componentService->getThreshold());

        test->runTest();
        m_tests.push_back(test);

        std::cout << "AAA " << m_componentService->getReferenceFileName() << std::endl;
    }
}

int AdvancedFunctionalMultiTest::analyseResults()
{
    ETestResult status = SUCCESS;
    for(size_t i=0; i<m_tests.size(); ++i) {
        if(m_tests[i]->analyseResults() != SUCCESS)
            status = FAILED;
    }

    AdvancedFunctionalTestInfo info = m_componentService->getTestInfo();

    std::cout << Utils::AdjustStringLength(info.m_test_name, 20) << " "
              << Utils::AdjustStringLength(info.m_test_description, 40) << " "
              << (status==SUCCESS ? "[OK]" : "[FAILED]") << std::endl;

    return status;
}


/*
std::ostringstream sdiff;
sdiff << std::setprecision(4) << diff;

std::string status("OK");
if(diff > threshold) {
    status = "FAILED";
    success = false;
}

std::cout << Utils::AdjustStringLength(it->first->getName(), 30)
          << " " << Utils::AdjustStringLength(it->second, 40)
          << " " << Utils::AdjustStringLength(sdiff.str(), 10)
          << "   " << status
          << std::endl;


*/
