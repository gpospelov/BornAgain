// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS11.cpp
//! @brief     Implements class TestIsGISAXS11.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS11.h"
#include "IsGISAXS11.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS11::TestIsGISAXS11() : IFunctionalTest("TestIsGISAXS11")
{
    setOutputPath(Utils::FileSystem::GetPathToData("../Tests/ReferenceData/IsGISAXS/ex-11/" ));
}


void TestIsGISAXS11::execute()
{
    FunctionalTests::IsGISAXS11 test;
    test.run();

    OutputDataIOFactory::writeIntensityData(*test.getOutputData(), "this_core_shell_qxqy.ima");
}


void TestIsGISAXS11::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_core_shell_qxqy.ima.gz");
    std::string this_file("this_core_shell_qxqy.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::readIntensityData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::readIntensityData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS11_c1", "Core shell parallelepiped islands");

    delete isgi_data;
    delete our_data;
}



