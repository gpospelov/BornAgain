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
#include "StandardFitsFactory.h"
#include <boost/scoped_ptr.hpp>

int fit_functional_test(const std::string &test_name)
{
    StandardFitsFactory catalogue;
    if (!catalogue.isValidTest(test_name)) {
        std::cout << "fit_functional_test() -> Non existing test with name '" << test_name << "', "
                  << "use argument from the list of defined tests" << std::endl;
        catalogue.printCatalogue(std::cout);
        return 1;
    }

    boost::scoped_ptr<IFunctionalTest> test(catalogue.createTest(test_name));
    test->runTest();
    return test->analyseResults();
}
