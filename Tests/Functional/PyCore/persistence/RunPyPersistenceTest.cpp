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
#include <string>

//! Runs PyPersistenceTest on a standard simulation indicated by argv[1].
int main(int argc, char** argv)
{
    if(argc<3){
        std::cout
            << "Usage: " << argv[0] << " <directory> <script name> [<threshold>]\n"
            << "  where <script name> is the stem without extension '.py',\n"
            << "        <threshold>   is a real number that defines the maximum average relative\n"
            << "                        difference between script output and reference data\n";
        std::exit(1);
    }
    double threshold;
    try {
        threshold = std::stod(argv[3]);
    } catch(std::invalid_argument) {
        std::cerr << "Cannot convert 3rd argument '" << argv[3] << "' to double\n";
        std::exit(1);
    }
    PyPersistenceTest test(argv[1], argv[2], threshold);
    test.runTest();
    return test.getTestResult();
}
