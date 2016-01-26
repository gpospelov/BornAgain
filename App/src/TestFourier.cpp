// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFourier.cpp
//! @brief     Implements class TestFourier.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFourier.h"

#include "GISASSimulation.h"
#include "Units.h"
#include "Utils.h"
#include "IsGISAXSTools.h"
#include "SampleFactory.h"
#include "TestMesoCrystal1.h"
#include "OutputDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "FileSystem.h"

TestFourier::TestFourier()
: mp_intensity_output(0)
, mp_sample(0)
{
}

TestFourier::~TestFourier()
{
    delete mp_intensity_output;
    delete mp_sample;
}

void TestFourier::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    initializeSample();
    GISASSimulation simulation(mp_options);
    simulation.setSample(*mp_sample);
    simulation.setDetectorParameters(256, 0.3*Units::degree, 10.0*Units::degree
            ,256, 0.0*Units::degree, 10.0*Units::degree);
    simulation.setBeamParameters(1.77*Units::angstrom, 0.4*Units::degree, 0.0*Units::degree);
    simulation.setBeamIntensity(8e12);

    simulation.runSimulation();
    //simulation.normalize();

    mp_intensity_output = simulation.getDetectorIntensity();
    OutputData<complex_t> fft_map;
    OutputDataFunctions::FourierTransform(*mp_intensity_output, &fft_map);
    OutputData<double> *p_real_fft_map = OutputDataFunctions::getModulusPart(fft_map);
    OutputDataFunctions::FourierTransformR(fft_map, mp_intensity_output);
    IsGISAXSTools::drawOutputData(*p_real_fft_map, "c1_four", "Fourier transform",
            "CONT4 Z", "Fourier transform");
    IntensityDataIOFactory::writeOutputData(*p_real_fft_map, Utils::FileSystem::GetHomePath()+"./Examples/MesoCrystals/Fourier.ima");
}


void TestFourier::initializeSample()
{
    delete mp_sample;
    mp_sample = SampleFactory::createSample("IsGISAXS11_CoreShellParticle");
}

//void TestFourier::initializeSample()
//{
//    delete mp_sample;
//    MesoCrystalBuilder builder;
//    mp_sample = builder.buildSample();
//}


