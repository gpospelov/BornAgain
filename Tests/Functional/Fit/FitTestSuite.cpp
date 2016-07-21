// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitTestSuite.cpp
//! @brief     Implements program FitTestSuite to run fit functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMinimizerTest.h"
#include "StandardFitsFactory.h"
#include <memory>
#include <iostream>

//! Runs functional tests.

int main(int argc, char **argv)
{
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);

    StandardFitsFactory catalogue;
    if (!catalogue.isValidTest(test_name)) {
        std::cout << "fit_functional_test() -> Non existing test with name '" << test_name << "', "
                  << "use argument from the list of defined tests" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    const std::unique_ptr<IFunctionalTest> test(catalogue.createTest(test_name));
    test->runTest();
    return test->analyseResults();
}
