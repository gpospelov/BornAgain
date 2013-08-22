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


TestPolarizedDWBA::TestPolarizedDWBA()
: mp_sample(0)
{
    std::cout << "TestPolarizedDWBA::TestPolarizedDWBA() -> Info."
            << std::endl;
}

void TestPolarizedDWBA::execute()
{
    std::cout << "TestPolarizedDWBA::execute() -> Info." << std::endl;

    // create sample
    mp_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample(
            "PolarizedDWBATestCase"));

    // calculate scattered intesity from sample
    Simulation simulation(mp_options);
    simulation.setDetectorParameters(
        100, -1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.setBeamIntensity(8e12);

    // Run simulation
    simulation.setSample(*mp_sample);
    simulation.runSimulation();

    simulation.normalize();

    IsGISAXSTools::drawLogOutputDataPol(*simulation.getPolarizedOutputData(),
            "c1_polDWBA", "Polarized DWBA", "CONT4 Z", "Polarized DWBA");

    delete mp_sample;

}

