#include "TestIsGISAXS15.h"
#include "IsGISAXS015.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS15::TestIsGISAXS15() : IFunctionalTest("TestIsGISAXS15")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-15/" );
}


void TestIsGISAXS15::execute()
{
    FunctionalTests::IsGISAXS015 test;
    test.run();

    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_SSCA.ima");
}


void TestIsGISAXS15::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_SSCA.ima");
    std::string this_file(getOutputPath()+"this_SSCA.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS15_c1", "SSCA Cylinders");

    delete isgi_data;
    delete our_data;
}

