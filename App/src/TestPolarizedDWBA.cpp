// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPolarizedDWBA.cpp
//! @brief     Implements class TestPolarizedDWBA.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestPolarizedDWBA.h"

#include "SampleFactory.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "SimulationRegistry.h"
#include "OutputDataIOFactory.h"
#include "FileSystem.h"


TestPolarizedDWBA::TestPolarizedDWBA()
: mp_sample(0)
{
    std::cout << "TestPolarizedDWBA::TestPolarizedDWBA() -> Info."
            << std::endl;
}

void TestPolarizedDWBA::execute()
{
    std::cout << "TestPolarizedDWBA::execute() -> Info." << std::endl;

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("magcyl2");
    simulation->setProgramOptions(mp_options);


    simulation->runSimulation();
    simulation->normalize();

    IsGISAXSTools::drawLogOutputDataPol(*simulation->getPolarizedOutputData(),
            "c1_polDWBA", "Polarized DWBA", "CONT4 Z", "Polarized DWBA");

//    OutputDataIOFactory::writeIntensityData(*simulation->getPolarizedIntensityData(0,0),"magcyl2_reference_00.txt");
//    OutputDataIOFactory::writeIntensityData(*simulation->getPolarizedIntensityData(0,1),"magcyl2_reference_01.txt");
//    OutputDataIOFactory::writeIntensityData(*simulation->getPolarizedIntensityData(1,0),"magcyl2_reference_10.txt");
//    OutputDataIOFactory::writeIntensityData(*simulation->getPolarizedIntensityData(1,1),"magcyl2_reference_11.txt");


//    OutputData<double> *reference00 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_00.txt.gz");
//    OutputData<double> *reference01 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_01.txt.gz");
//    OutputData<double> *reference10 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_10.txt.gz");
//    OutputData<double> *reference11 = OutputDataIOFactory::readIntensityData(Utils::FileSystem::GetReferenceDataDir()+ "magcyl2_reference_11.txt.gz");

//    IsGISAXSTools::drawOutputDataComparisonResults(
//            *simulation->getPolarizedIntensityData(0,0), *reference00, "00", "found params");

//    IsGISAXSTools::drawOutputDataComparisonResults(
//            *simulation->getPolarizedIntensityData(0,1), *reference01, "01", "found params");

//    IsGISAXSTools::drawOutputDataComparisonResults(
//            *simulation->getPolarizedIntensityData(1,0), *reference10, "10", "found params");

//    IsGISAXSTools::drawOutputDataComparisonResults(
//            *simulation->getPolarizedIntensityData(1,1), *reference11, "11", "found params");


//    delete reference00;
//    delete reference01;
//    delete reference10;
//    delete reference11;

    delete simulation;

}

