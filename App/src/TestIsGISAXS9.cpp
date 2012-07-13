#include "TestIsGISAXS9.h"
#include "IsGISAXSTools.h"
#include "InterferenceFunctionNone.h"
#include "Types.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "NanoParticleDecoration.h"
#include "NanoParticle.h"
#include "LayerDecorator.h"
#include "GISASExperiment.h"
#include "FormFactors.h"

#include "TCanvas.h"

TestIsGISAXS9::TestIsGISAXS9()
    : mp_sample(0), mp_intensity_output(0)
{
}

TestIsGISAXS9::~TestIsGISAXS9()
{
    delete mp_sample;
    delete mp_intensity_output;
}


void TestIsGISAXS9::initialise()
{
    initializeSample();
}


void TestIsGISAXS9::execute()
{
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(0.0*Units::degree, 2.0*Units::degree, 100
            , 0.0*Units::degree, 2.0*Units::degree, 100, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    if (mp_intensity_output) delete mp_intensity_output;
    mp_intensity_output = experiment.getOutputData();

    // saving results to file
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z0.ima");

}


void TestIsGISAXS9::finalise()
{
    // reading result of IsGISAXS for comparison
    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/isgi_pyramid_Z0.ima");

    // ploting results
    TCanvas *c1 = new TCanvas("TestIsGISAXS9_c1", "Pyramid DWBA formfactor", 1024, 768);
    c1->Divide(2,2);

    // our calculations
    c1->cd(1);
    IsGISAXSTools::drawLogOutputDataInCurrentPad(*mp_intensity_output, "CONT4 Z", "Calculated pyramid FF");
    // isgisaxs data
    c1->cd(2);
    IsGISAXSTools::drawLogOutputDataInCurrentPad(*isgi_data, "CONT4 Z", "IsGisaxs pyramid FF");
    // difference between two
    OutputData<double> *difference = mp_intensity_output->clone();
    c1->cd(3);
    *difference -= *isgi_data;
    IsGISAXSTools::drawLogOutputDataInCurrentPad(*difference, "CONT4 Z", "Difference");

    delete isgi_data;
    delete difference;
}


void TestIsGISAXS9::initializeSample()
{
    if(mp_sample) delete mp_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}
