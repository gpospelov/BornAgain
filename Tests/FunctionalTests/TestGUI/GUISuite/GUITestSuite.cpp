// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/FunctionalTests/TestGUI/GUISuite/GUITestSuite.cpp
//! @brief     Implements program GUISuite to run gui functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FunctionalTestRegistry.h"
#include "GUIFunctionalTestComponentService.h"
#include "FunctionalMultiTest.h"
#include <iostream>

//! The main function of GUITestSuite to run functional tests
int main(int argc, char **argv)
{
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);

    FunctionalTestRegistry catalogue;
    if (!catalogue.isValidTest(test_name)) {
        if(test_name!="")
            std::cout<<"There is no test named '"<< test_name << "'" << std::endl;
        std::cout << "Usage: GUISuite <test_name>" << std::endl;
        std::cout << "Available tests:" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    FunctionalTestInfo info = catalogue.getTestInfo(test_name);

    GUIFunctionalTestComponentService *service = new GUIFunctionalTestComponentService(info);
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
