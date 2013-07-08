// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS10.cpp
//! @brief     Implements class TestIsGISAXS10.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS10.h"
#include "IsGISAXS10.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS10::TestIsGISAXS10() : IFunctionalTest("TestIsGISAXS10")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Tests/ReferenceData/IsGISAXS/ex-10/" );
}


void TestIsGISAXS10::execute()
{
    FunctionalTests::IsGISAXS10 test;
    test.run();

    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_para1dcyl.ima");
}


void TestIsGISAXS10::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_para1dcyl.ima.gz");
    std::string this_file(getOutputPath()+"this_para1dcyl.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS10_c1", "1D paracrystal cylinder islands");

    delete isgi_data;
    delete our_data;
}


