// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS2.cpp
//! @brief     Implements class TestIsGISAXS2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "TestIsGISAXS2.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include <fstream>


TestIsGISAXS2::TestIsGISAXS2() : IFunctionalTest("TestIsGISAXS2")
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/IsGISAXS/ex-2/" ));
}


void TestIsGISAXS2::execute()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs02");

    Simulation simulation(mp_options);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.setSample(*sample);
    simulation.runSimulation();

    OutputDataIOFactory::writeIntensityData(*simulation.getOutputData(), "this_bimodal.ima");
}


void TestIsGISAXS2::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_bimodal.ima.gz");
    std::string this_file("this_bimodal.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::readIntensityData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::readIntensityData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS2_c1", "Mixture of cylindrical particles with different size distribution");

    delete isgi_data;
    delete our_data;
}



