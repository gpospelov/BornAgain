// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IFunctionalTest.cpp
//! @brief     Implements IFunctionalTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFunctionalTest.h"
#include <iostream>

IFunctionalTest::~IFunctionalTest() = default;

bool IFunctionalTest::execute()
{
    bool success(false);

    try {
        success = runTest();
    } catch (std::exception &ex) {
        std::cout << "IFunctionalTest::execute() -> Error. Exception was caught '"
                  << ex.what() << "'" << std::endl;
    }
    return success;
}
