// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFunctionalTests.cpp
//! @brief     Implements class TestFunctionalTests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFunctionalTests.h"
#include "ProgramOptions.h"
#include "IsGISAXSTools.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "IFunctionalTest.h"
#include <memory>
#include <iostream>
#include <vector>
#include <string>


// FIXME either refactor to the new functional tests machinery, or remove the code
void TestFunctionalTests::execute()
{
//    if(!readTestNames()) return;

//    for(size_t i=0; i<m_testNames.size(); ++i) {
//        const std::unique_ptr<IFunctionalTest> test(m_testRegistry.getTest(m_testNames[i]));
//        test->getSimulation()->setProgramOptions(mp_options);
//        test->runTest();
//        test->analyseResults();

//        IntensityDataIOFactory::writeIntensityData(*test->getSimulation()->getOutputData(), "a.int");

//        const std::unique_ptr<OutputData<double> > result_data(test->getSimulation()->getIntensityData());
//        double diff = IntensityDataFunctions::getRelativeDifference(*result_data.get(), *test->getReference());
//        std::cout << "diff: " << diff << std::endl;

//        IsGISAXSTools::drawOutputDataComparisonResults( *result_data.get(),
//            *test->getReference(), test->getName(), test->getDescription());
//   }
}

bool TestFunctionalTests::readTestNames()
{
//    if (mp_options->find("functest")) {
//        m_testNames = (*mp_options)["functest"].as<std::vector<std::string> >();
//    }

//    bool areCorrectNames(true);
//    if(m_testNames.empty()) {
//        std::cout << std::endl << "TestFunctionalTest::readTestNames() -> Info. No tests specified. Select one or more from list below." << std::endl;
//        areCorrectNames = false;
//    }

//    for(size_t i=0; i<m_testNames.size(); ++i) {
//        if(!m_testRegistry.isRegisteredName(m_testNames[i])) {
//            std::cout << "TestFunctionalTest::readTestNames() -> Info. Not registered test with name '" << m_testNames[i] << "'." << std::endl;
//            areCorrectNames = false;
//        }
//    }

//    if(areCorrectNames) {
//        return true;
//    } else {
//        m_testRegistry.printCatalogue();
//        std::cout << std::endl;
//        return false;
//    }
    return false;
}
