// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/core_functional_test.h
//! @brief     Implements program CoreSuite, to run core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestRegistry.h"
#include "FunctionalMultiTest.h"
#include "CoreFunctionalTestComponentService.h"
#include <iostream>

//! Program CoreSuite, to run core functional tests.
int main(int argc, char** argv)
{
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);

    FunctionalTestRegistry catalogue;
    if (!catalogue.isValidTest(test_name)) {
        if(test_name!="")
            std::cout<<"There is no test named '"<< test_name << "'" << std::endl;
        std::cout << "Usage: CoreSuite <test_name>" << std::endl;
        std::cout << "Available tests:" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    FunctionalTestInfo info = catalogue.getTestInfo(test_name);

    CoreFunctionalTestComponentService* service = new CoreFunctionalTestComponentService(info);
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
