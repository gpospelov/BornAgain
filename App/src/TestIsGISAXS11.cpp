#include "TestIsGISAXS11.h"
#include "IsGISAXS011.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS11::TestIsGISAXS11() : IFunctionalTest("TestIsGISAXS11")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-11/" );
}


void TestIsGISAXS11::execute()
{
    FunctionalTests::IsGISAXS011 test;
    test.run();

    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_core_shell_qxqy.ima");
}


void TestIsGISAXS11::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_core_shell_qxqy.ima.gz");
    std::string this_file(getOutputPath()+"this_core_shell_qxqy.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS11_c1", "Core shell parallelepiped islands");

    delete isgi_data;
    delete our_data;
}

