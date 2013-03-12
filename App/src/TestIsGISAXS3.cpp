#include "TestIsGISAXS3.h"
#include "IsGISAXS03.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS3::TestIsGISAXS3() : IFunctionalTest("TestIsGISAXS3")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/" );
}


void TestIsGISAXS3::execute()
{
    FunctionalTests::IsGISAXS03 test;
    test.runDWBA();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS03::kTest_DWBA), getOutputPath()+"this_cylinder_DWBA.ima");
    test.runBA();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS03::kTest_BA), getOutputPath()+"this_cylinder_BA.ima");
    test.runBA_Size();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS03::kTest_BASize), getOutputPath()+"this_cylinder_BA_size.ima");
}


void TestIsGISAXS3::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cylinder_BA.ima.gz",      getOutputPath()+"this_cylinder_BA.ima",
                                       "Cylinder BA Formfactor") );
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cylinder_BA_size.ima.gz", getOutputPath()+"this_cylinder_BA_size.ima",
                                       "Cylinder BA Formfactor with size distribution") );
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cylinder_DWBA.ima.gz",    getOutputPath()+"this_cylinder_DWBA.ima",
                                       "Cylinder DWBA Formfactor") );

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(tocompare[i].isginame);
        OutputData<double> *our_data = OutputDataIOFactory::getOutputData(tocompare[i].thisname);

        IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, tocompare[i].descr, tocompare[i].descr);

        delete isgi_data;
        delete our_data;
    }
}
