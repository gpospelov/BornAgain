// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPolarizedDWBA.cpp
//! @brief     Implements class TestPolarizedDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestPolarizedDWBA.h"

#include "SampleFactory.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "SimulationRegistry.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"


TestPolarizedDWBA::TestPolarizedDWBA()
{
    std::cout << "TestPolarizedDWBA::TestPolarizedDWBA() -> Info."
            << std::endl;
}

void TestPolarizedDWBA::execute()
{
    std::cout << "TestPolarizedDWBA::execute() -> Info." << std::endl;

    SimulationRegistry sim_registry;
    GISASSimulation *simulation = sim_registry.createSimulation("magcyl2");
    simulation->setProgramOptions(mp_options);

    simulation->runSimulation();
    //simulation->normalize();

    IsGISAXSTools::drawLogOutputData(*simulation->getOutputData(),
            "c1_polDWBA", "Polarized DWBA", "CONT4 Z", "Polarized DWBA");

    delete simulation;
}

