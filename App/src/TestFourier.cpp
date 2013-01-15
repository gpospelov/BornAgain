#include "TestFourier.h"

#include "GISASExperiment.h"
#include "Units.h"
#include "Utils.h"
#include "IsGISAXSTools.h"
#include "SampleFactory.h"
#include "TestMesoCrystal1.h"
#include "OutputDataFunctions.h"
#include "OutputDataIOFactory.h"

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
    GISASExperiment experiment(mp_options);
    experiment.setSample(*mp_sample);
    experiment.setDetectorParameters(256, 0.3*Units::degree, 10.0*Units::degree
            ,256, 0.0*Units::degree, 10.0*Units::degree);
    experiment.setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    experiment.setBeamIntensity(8e12);

    experiment.runSimulation();
    experiment.normalize();

    mp_intensity_output = experiment.getOutputDataClone();
    OutputData<complex_t> fft_map;
    OutputDataFunctions::fourierTransform(*mp_intensity_output, &fft_map);
    OutputData<double> *p_real_fft_map = OutputDataFunctions::getModulusPart(fft_map);
    OutputDataFunctions::fourierTransformR(fft_map, mp_intensity_output);
    IsGISAXSTools::drawOutputData(*p_real_fft_map, "c1_four", "Fourier transform",
            "CONT4 Z", "Fourier transform");
    OutputDataIOFactory::writeOutputData(*p_real_fft_map, Utils::FileSystem::GetHomePath()+"./Examples/MesoCrystals/fourier.ima");
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
