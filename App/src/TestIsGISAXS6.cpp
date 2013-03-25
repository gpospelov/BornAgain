// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS6.cpp 
//! @brief     Implements class TestIsGISAXS6.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "TestIsGISAXS6.h"
#include "IsGISAXS06.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS6::TestIsGISAXS6() : IFunctionalTest("TestIsGISAXS6")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-6/" );
}


void TestIsGISAXS6::execute()
{
    FunctionalTests::IsGISAXS06 test;

    test.runlattice();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS06::kTest_Lattice), getOutputPath()+"this_lattice.ima");

    test.runcentered();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS06::kTest_Centered), getOutputPath()+"this_centered.ima");

    test.runrotated();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS06::kTest_Rotated), getOutputPath()+"this_rotated.ima");

    test.runvariants();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS06::kTest_Variants), getOutputPath()+"this_variants.ima");
}


void TestIsGISAXS6::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_lattice.ima.gz",      getOutputPath()+"this_lattice.ima",      "Cylinder 2D lattice") );
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_centered.ima.gz",     getOutputPath()+"this_centered.ima",     "Cylinder 2D lattice centered") );
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_rotated.ima.gz",      getOutputPath()+"this_rotated.ima",      "Cylinder 2D lattice rotated") );
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_variants.ima.gz",     getOutputPath()+"this_variants.ima",     "Cylinder 2D lattice variants") );

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(tocompare[i].isginame);
        OutputData<double> *our_data = OutputDataIOFactory::getOutputData(tocompare[i].thisname);

        IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, tocompare[i].descr, tocompare[i].descr);

        delete isgi_data;
        delete our_data;
    }
}
