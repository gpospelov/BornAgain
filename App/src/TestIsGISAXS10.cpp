#include "TestIsGISAXS10.h"
#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "Utils.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "LayerDecorator.h"
#include "NanoParticleDecoration.h"

#include "TCanvas.h"
#include "TH2.h"
#include "TStyle.h"

#include <fstream>


TestIsGISAXS10::TestIsGISAXS10()
    : mp_sample(0), mp_intensity_output(0)
{
}

TestIsGISAXS10::~TestIsGISAXS10()
{
    delete mp_sample;
    delete mp_intensity_output;
}

void TestIsGISAXS10::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    initializeSample();
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(0.0*Units::degree, 2.0*Units::degree, 100
            , 0.0*Units::degree, 2.0*Units::degree, 100, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    mp_intensity_output = experiment.getOutputData();
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_isgisaxs_10", "1D paracrystal islands",
            "CONT4 Z");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-10/para1dcyl.ima");
}

void TestIsGISAXS10::initializeSample()
{
    delete mp_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-5e-6, 2e-8);
    complex_t n_particle(1.0-5e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,
            7*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}

// The next sample was for testing particles inside substrate and is now obsolete
void TestIsGISAXS10::initializeSample2()
{
    delete mp_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-5e-6, 2e-8);
    complex_t n_particle(1.0-5e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion_1 = new InterferenceFunctionNone();
//    IInterferenceFunction *p_interference_funtion_2 = new InterferenceFunctionNone();
    NanoParticleDecoration particle_decoration;
    particle_decoration.addNanoParticle(new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),
                0*Units::nanometer, 0.5);
    particle_decoration.addNanoParticle(new NanoParticle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)),
            0*Units::nanometer, 0.5);
    particle_decoration.addInterferenceFunction(p_interference_funtion_1);
//    particle_decoration.addInterferenceFunction(p_interference_funtion_2);
    LayerDecorator substrate_layer_decorator(substrate_layer, particle_decoration);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}

