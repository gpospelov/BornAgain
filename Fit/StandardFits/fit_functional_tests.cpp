// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardFits/fit_functional_test.h
//! @brief     Implements function to run all fit functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "fit_functional_tests.h"
#include "IMinimizerFunctionalTest.h"
//#include "FunctionalTestRegistry.h"
//#include "FunctionalMultiTest.h"
//#include "CoreFunctionalTestComponentService.h"
//#include <boost/scoped_ptr.hpp>
//#include <iostream>

int fit_functional_test(const std::string &test_name)
{
//    FunctionalTestRegistry catalogue;
//    if (!catalogue.isValidTest(test_name)) {
//        std::cout << "CORE_FUNCTIONAL_TEST() -> Non existing test with name '" << test_name << "', "
//                  << "use argument from the list of defined tests" << std::endl;
//        catalogue.printCatalogue(std::cout);
//        return 1;
//    }

//    FunctionalTestInfo info = catalogue.getTestInfo(test_name);

//    CoreFunctionalTestComponentService *service = new CoreFunctionalTestComponentService(info);
//    boost::scoped_ptr<IFunctionalTest> test(
//        new FunctionalMultiTest(test_name, service));
//    test->runTest();
//    return test->analyseResults();

    IMinimizerFunctionalTest test("Minuit2", "Migrad");
    test.runTest();
    return test.analyseResults();
}
