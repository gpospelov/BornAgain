// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.cpp
//! @brief     Implements TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestUtils.h"
#include "StandardTestCatalogue.h"
#include <iostream>

StandardTestInfo TestUtils::testInfo(int argc, char** argv)
{
    static StandardTestCatalogue catalogue = StandardTestCatalogue();

    std::string test_name = argc>1 ? std::string(argv[1]) : std::string();

    if (!catalogue.contains(test_name)) {
        std::cout<<"There is no test named '"<< test_name << "'\n";
        std::cout << "Available tests:\n";
        catalogue.printCatalogue(std::cout);
        return StandardTestInfo();
    }

    return catalogue.testInfo(test_name);
}
