// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS15.cpp
//! @brief     Implements class TestIsGISAXS15.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS15.h"
#include "IsGISAXS15.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS15::TestIsGISAXS15() : IFunctionalTest("TestIsGISAXS15")
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/IsGISAXS/ex-15/" ));
}


void TestIsGISAXS15::execute()
{
    FunctionalTests::IsGISAXS15 test;
    test.run();

    OutputDataIOFactory::writeIntensityData(*test.getOutputData(), "this_SSCA.ima");
}


void TestIsGISAXS15::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_SSCA.ima");
    std::string this_file("this_SSCA.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::readIntensityData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::readIntensityData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS15_c1", "SSCA Cylinders");

    delete isgi_data;
    delete our_data;
}



