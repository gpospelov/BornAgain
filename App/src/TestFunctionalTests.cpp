#include "TestFunctionalTests.h"
#include "ProgramOptions.h"
#include "MessageService.h"
#include "IsGISAXSTools.h"
#include <iostream>
#include <vector>
#include <string>


void TestFunctionalTests::execute()
{
    std::cout << "TestFunctionalTest::execute() -> Hello World." << std::endl;

   if(!readTestNames()) return;

   for(size_t i=0; i<m_testNames.size(); ++i) {
       m_testRegistry.runTest(m_testNames[i]);

       //IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS1_c1", "Two particles mean DWBA Formfactor");

   }

}



bool TestFunctionalTests::readTestNames()
{
    if (mp_options->find("functest")) {
        m_testNames = (*mp_options)["functest"].as<std::vector<std::string> >();
    }

    bool areCorrectNames(true);
    if(m_testNames.empty()) {
        std::cout << std::endl << "TestFunctionalTest::readTestNames() -> Info. No tests specified. Select one or more from list below." << std::endl;
        areCorrectNames = false;
    }

    for(size_t i=0; i<m_testNames.size(); ++i) {
        if(!m_testRegistry.isRegisteredName(m_testNames[i])) {
            std::cout << "TestFunctionalTest::readTestNames() -> Info. Not registered test with name '" << m_testNames[i] << "'." << std::endl;
            areCorrectNames = false;
        }
    }

    if(areCorrectNames) {
        return true;
    } else {
        m_testRegistry.printCatalogue();
        std::cout << std::endl;
        return false;
    }
}
