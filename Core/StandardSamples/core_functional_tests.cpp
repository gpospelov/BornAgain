// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/core_functional_test.h
//! @brief     Implements function to run all core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "core_functional_tests.h"
#include "FunctionalTestRegistry.h"
#include "FunctionalMultiTest.h"
#include "CoreFunctionalTestComponentService.h"
#include <iostream>

//! Runs a functional test and returns error code.
//! Note the analogy with PYSCRIPT_FUNCTIONAL_TEST and GUI_FUNCTIONAL_TEST.

int CORE_FUNCTIONAL_TEST(const std::string &test_name)
{
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

    CoreFunctionalTestComponentService *service = new CoreFunctionalTestComponentService(info);
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
