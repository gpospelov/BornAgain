#include "TestIsGISAXS7.h"
#include "IsGISAXS07.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS7::TestIsGISAXS7() : IFunctionalTest("TestIsGISAXS7")
{
   setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-7/" );
}


void TestIsGISAXS7::execute()
{
    FunctionalTests::IsGISAXS07 test;
    test.run();

    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_morphology.ima");

}


void TestIsGISAXS7::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_morphology.ima.gz");
    std::string this_file(getOutputPath()+"this_morphology.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS7_c1", "Morphology");

    delete isgi_data;
    delete our_data;
}
