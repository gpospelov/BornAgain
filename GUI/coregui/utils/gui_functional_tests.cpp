// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/gui_functional_test.h
//! @brief     Implements function to run all gui functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "gui_functional_tests.h"
#include "FunctionalTestRegistry.h"
#include "GUIFunctionalTestComponentService.h"
#include "FunctionalMultiTest.h"
#include <memory>
#include <iostream>

int GUI_FUNCTIONAL_TEST(const std::string &test_name)
{
    FunctionalTestRegistry catalogue;
    if (!catalogue.isValidTest(test_name)) {
        std::cout << "GUI_FUNCTIONAL_TEST() -> Non existing test with name '" << test_name << "', "
                  << "use argument from the list of defined tests" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    FunctionalTestInfo info = catalogue.getTestInfo(test_name);

    GUIFunctionalTestComponentService *service = new GUIFunctionalTestComponentService(info);
    std::unique_ptr<IFunctionalTest> test(
        new FunctionalMultiTest(test_name, service));

    test->runTest();
    return test->analyseResults();
}
