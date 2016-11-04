// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITranslationTest/main.cpp
//! @brief     Implements main to run GUI translation tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include <iostream>
#include "GUITranslationTest.h"

bool run_tests() {

    std::vector<std::pair<std::string, std::string>> conditions = {
        {"BasicGISAS", "CylindersAndPrismsBuilder"},
        {"BasicGISAS", "RadialParaCrystalBuilder"},
        {"BasicGISAS", "Lattice1DBuilder"},
        //{"BasicGISAS", "Basic2DParaCrystalBuilder"},
        {"BasicGISAS", "Basic2DLatticeBuilder"},
        {"BasicGISAS", "SquareLatticeBuilder"},
    };

    bool success(true);
    for(auto pair: conditions)
        success &= GUITranslationTest(pair.first, pair.second).runTest();

    if(!success)
        std::cout << "Failure!" << std::endl;

    return success;
}

int main(int , char**)
{
    return run_tests() == true ? 0 : 1;
}
