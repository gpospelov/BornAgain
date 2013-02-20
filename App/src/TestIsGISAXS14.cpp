#include "TestIsGISAXS14.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include "Simulation.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "Units.h"

#include <fstream>


TestIsGISAXS14::TestIsGISAXS14() : IFunctionalTest("TestIsGISAXS14")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-14/" );
}


void TestIsGISAXS14::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS14_LayeredSpheresOnGradedInterface"));

    Simulation simulation(mp_options);
    simulation.setSample(*sample);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputDataClone(), getOutputPath() + "this_multilayer_sphere.ima");
}


void TestIsGISAXS14::finalise()
{
    //std::string isgi_file(getOutputPath()+"isgi_normal_sphere_H2.0.ima");
    std::string isgi_file(getOutputPath()+"test_this_fullsphere.ima");
//    std::string isgi_file(getOutputPath()+"isgi_normal_sphere_H2.0_nocorr.ima");
//    std::string isgi_file(getOutputPath()+"isgi_normal_fullsphere_nocorr.ima");
//    std::string this_file(getOutputPath()+"this_multilayer_sphere_nocorr.ima");
    std::string this_file(getOutputPath()+"this_multilayer_sphere.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS14_c1", "Multilayered sphere on graded interface");

    delete isgi_data;
    delete our_data;
}
