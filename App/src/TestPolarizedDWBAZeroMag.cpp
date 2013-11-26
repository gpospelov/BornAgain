// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPolarizedDWBAZeroMag.cpp
//! @brief     Implements class TestPolarizedDWBAZeroMag.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestPolarizedDWBAZeroMag.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "SampleFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "SimulationRegistry.h"

TestPolarizedDWBAZeroMag::TestPolarizedDWBAZeroMag()
: IFunctionalTest("TestPolarizedDWBAZeroMag")
{
    setOutputPath(Utils::FileSystem::GetPathToData(
            "../Tests/ReferenceData/IsGISAXS/ex-3/" ));
}


void TestPolarizedDWBAZeroMag::execute()
{
    // building simulation
    //Simulation simulation(mp_options);
    //simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
     //                                100, 0.0*Units::degree, 2.0*Units::degree,
    //                                 true);
    //simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
    //        0.0*Units::degree);

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("PolarizedDWBAZeroMag");


    // test1
//    ISample *sample = SampleFactory::createSample(
//            "PolarizedDWBAZeroMagTestCase");
//    simulation.setSample(*sample);

    simulation->runSimulation();
    m_result = simulation->getIntensityData();

//    OutputDataIOFactory::writeIntensityData(*m_result,
//            "this_cylinder_DWBA_pol.ima");
//    delete sample;

}

void TestPolarizedDWBAZeroMag::finalise()
{
//    std::vector< CompareStruct > tocompare;
//    tocompare.push_back( CompareStruct(
//            getOutputPath()+"isgi_cylinder_DWBA.ima.gz",
//            "this_cylinder_DWBA_pol.ima",
//            "Cylinder DWBA Formfactor with matrix calculation") );

//    for(size_t i=0; i<tocompare.size(); ++i) {
//        OutputData<double> *isgi_data = OutputDataIOFactory::readIntensityData(
//                tocompare[i].isginame);
//        OutputData<double> *our_data = OutputDataIOFactory::readIntensityData(
//                tocompare[i].thisname);

        OutputData<double> *reference = OutputDataIOFactory::readIntensityData(
                        getOutputPath()+"isgi_cylinder_DWBA.ima.gz");

        IsGISAXSTools::drawOutputDataComparisonResults(*m_result, *reference,
                                                       "zzz");

        delete reference;
}


