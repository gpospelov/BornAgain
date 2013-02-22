#include "TestIsGISAXS9.h"
#include "IsGISAXS09.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS9::TestIsGISAXS9() : IFunctionalTest("TestIsGISAXS9")
{
   setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/" );
}


void TestIsGISAXS9::execute()
{
    FunctionalTests::IsGISAXS09 test;
    test.runpyramidZ0();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_pyramid_Z0.ima");
    test.runpyramidZ45();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_pyramid_Z45.ima");

}


void TestIsGISAXS9::finalise()
{
            std::vector<std::string > isgi_files;
            isgi_files.push_back(getOutputPath()+"isgi_pyramid_Z0.ima.gz");
            isgi_files.push_back(getOutputPath()+"isgi_pyramid_Z45.ima.gz");

            std::vector<std::string > this_files;
            this_files.push_back(getOutputPath()+"this_pyramid_Z0.ima");
            this_files.push_back(getOutputPath()+"this_pyramid_Z45.ima");

            std::string descript[2];
            descript[0]="TestIsGISAXS9_c1";
            descript[1]="TestIsGISAXS9_c2";

            std::string titlegraph[2];
            titlegraph[0]="Pyramid DWBA formfactor";
            titlegraph[1]="Rotated pyramid DWBA formfactor";

            for(int i_comparison=0; i_comparison<2; i_comparison++) {
               OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_files[i_comparison]);
               OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_files[i_comparison]);

               std::cout <<descript[i_comparison] <<std::endl;
               IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data,descript[i_comparison] , titlegraph[i_comparison]);

                delete isgi_data;
                delete our_data;
        }

}
