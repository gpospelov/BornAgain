// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS8.cpp
//! @brief     Implements class TestIsGISAXS8.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS8.h"
#include "IsGISAXS08.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <fstream>


TestIsGISAXS8::TestIsGISAXS8() : IFunctionalTest("TestIsGISAXS8")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-8/" );
}


void TestIsGISAXS8::execute()
{
    FunctionalTests::IsGISAXS08 test;

    test.run2DDL();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS08::kTest_2DDL), getOutputPath()+"this_2DDL_lattice.ima");

    test.run2DDL2();
    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS08::kTest_2DDL2), getOutputPath()+"this_2DDL_lattice2.ima");
}


void TestIsGISAXS8::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_2DDL_lattice.ima.gz", getOutputPath()+"this_2DDL_lattice.ima", "Cylinder 2DDL lattice") );
    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_2DDL_lattice2.ima.gz", getOutputPath()+"this_2DDL_lattice2.ima", "Cylinder 2DDL lattice with isotropic pdfs") );

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(tocompare[i].isginame);
        OutputData<double> *our_data = OutputDataIOFactory::getOutputData(tocompare[i].thisname);

        IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, tocompare[i].descr, tocompare[i].descr);

        delete isgi_data;
        delete our_data;
    }
}



