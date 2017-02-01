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
            {"BasicGISAS", "CylindersAndPrismsBuilder"}
//            {"BasicGISAS", "RadialParaCrystalBuilder"},
//            {"BasicGISAS", "HexParaCrystalBuilder"},
//            {"BasicGISAS", "CoreShellParticleBuilder"},
        //    {"BasicGISAS", "MultiLayerWithRoughnessBuilder"},
//            {"BasicGISAS", "SquareLatticeBuilder"},
//            {"BasicGISAS", "RotatedPyramidsBuilder"},
//            {"BasicGISAS", "CylindersWithSizeDistributionBuilder"},
        //    {"BasicGISAS", "ParticleCompositionBuilder"},
//        {"BasicGISAS", "Basic2DParaCrystalBuilder"},
//            {"BasicGISAS", "Lattice1DBuilder"},
//            {"BasicGISAS", "Basic2DLatticeBuilder"}
    };

    bool success(true);
    for(auto pair: conditions) {
        bool current = GUITranslationTest(pair.first, pair.second).runTest();
        std::cout << "Sample: " << pair.second
                  << " --> " << (current ? "Success" : "Failure") << std::endl;
        success &= current;
    }

    std::cout << std::string(80, '-') << std::endl;
    std::cout << "Summary: " << (success ? "Success" : "Failure") << std::endl;

    return success;
}

int main(int , char**)
{
    return run_tests() == true ? 0 : 1;
}
