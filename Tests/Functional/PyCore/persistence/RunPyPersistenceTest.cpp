// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyPersistenceStandardTest.cpp
//! @brief     Implements program PyPersistenceStandardTest, to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyPersistenceTest.h"
#include <cstdlib>
#include <iostream>

//! Runs PyPersistenceTest on a standard simulation indicated by argv[1].
int main(int argc, char** argv)
{
    if(argc<3){
        std::cout << "Usage: " << argv[0] << " <scriptname [without extension .py]>\n";
        std::exit(1);
    }
    PyPersistenceTest test(argv[1]);
    test.runTest();
    std::cout << test << "\n";
    return test.getTestResult();
}
