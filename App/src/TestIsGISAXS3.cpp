// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestIsGISAXS3.cpp
//! @brief     Implements class TestIsGISAXS3.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestIsGISAXS3.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
//#include "IsGISAXS03.h"
#include <fstream>


TestIsGISAXS3::TestIsGISAXS3() : IFunctionalTest("TestIsGISAXS3")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Tests/ReferenceData/IsGISAXS/ex-3/" );
}


void TestIsGISAXS3::execute()
{
//    FunctionalTests::IsGISAXS03 test;
//    test.runDWBA();
//    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS03::kTest_DWBA), getOutputPath()+"this_cylinder_DWBA.ima");
//    test.runBA();
//    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS03::kTest_BA), getOutputPath()+"this_cylinder_BA.ima");
//    test.runBA_Size();
//    OutputDataIOFactory::writeOutputData(*test.getOutputData(FunctionalTests::IsGISAXS03::kTest_BASize), getOutputPath()+"this_cylinder_BA_size.ima");


    SampleBuilderFactory factory;

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // test1
    ISample *sample = factory.createSample("isgisaxs03_dwba");
    simulation.setSample(*sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), getOutputPath()+"this_cylinder_DWBA.ima");
    delete sample;

    // test2
    sample = factory.createSample("isgisaxs03_ba");
    simulation.setSample(*sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), getOutputPath()+"this_cylinder_BA.ima");
    delete sample;

    // test3
    sample = factory.createSample("isgisaxs03_basize");
    simulation.setSample(*sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), getOutputPath()+"this_cylinder_BA_size.ima");
    delete sample;

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


