// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS1.cpp 
//! @brief     Implements class TestIsGISAXS1.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "TestIsGISAXS1.h"
#include "IsGISAXS01.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS1::TestIsGISAXS1() : IFunctionalTest("TestIsGISAXS1")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-1/" );
}


void TestIsGISAXS1::execute()
{
    FunctionalTests::IsGISAXS01 test;
    test.run();

    OutputDataIOFactory::writeOutputData(*test.getOutputData(), getOutputPath()+"this_2-types-of-islands-ewald.ima");
}


void TestIsGISAXS1::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_2-types-of-islands-ewald.ima.gz");
    std::string this_file(getOutputPath()+"this_2-types-of-islands-ewald.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS1_c1", "Two particles mean DWBA Formfactor");

    delete isgi_data;
    delete our_data;
}
