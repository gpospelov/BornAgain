#include "TestFittingModule.h"
#include "Units.h"
#include "MathFunctions.h"
#include "GISASExperiment.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "NanoParticleDecoration.h"
#include "LayerDecorator.h"
#include "NanoParticle.h"
#include "FormFactors.h"

TestFittingModule::TestFittingModule()
: mp_exact_data(0)
, mp_real_data(0)
, mp_simulated_data(0)
, mp_sample(0)
{
}

TestFittingModule::~TestFittingModule()
{
    delete mp_exact_data;
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_sample;
}

void TestFittingModule::execute()
{
    // Generate exact sample simulation
    if (mp_exact_data) delete mp_exact_data;
    initializeSample();
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree
            ,100 , 0.0*Units::degree, 2.0*Units::degree);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    mp_exact_data = experiment.getOutputDataClone();
    // Generate noisy version
    generateRealData(0.2);
    IsGISAXSTools::drawLogOutputData(*mp_real_data, "c1_test_fitting", "fitting", "CONT4 Z");
//    IsGISAXSTools::writeOutputDataToFile(*mp_real_data, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-10/para1dcyl.ima");
}

void TestFittingModule::initializeSample()
{
    delete mp_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_layer(1.0-2e-6, 2e-8);
    complex_t n_substrate(1.0-5e-6, 2e-8);
    complex_t n_particle(1.0-5e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_layer_material = MaterialManager::instance().addHomogeneousMaterial("Layer", n_layer);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer layer_layer;
    layer_layer.setMaterial(p_layer_material);
    layer_layer.setThickness(10.0*Units::nanometer);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,
            7*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),
                10*Units::nanometer, 1.0);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator layer_decorator(layer_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}

void TestFittingModule::generateRealData(double noise_factor)
{
    if (mp_exact_data==0) {
        return;
    }
    if (mp_real_data) {
        delete mp_real_data;
    }
    mp_real_data = mp_exact_data->clone();
    mp_real_data->resetIndex();
    while (mp_real_data->hasNext()) {
        double current = mp_real_data->currentValue();
        double sigma = noise_factor*current;
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        mp_real_data->next() = random;
    }
}
