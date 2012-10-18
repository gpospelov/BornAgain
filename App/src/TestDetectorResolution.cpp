#include "TestDetectorResolution.h"

#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "MathFunctions.h"
#include "ResolutionFunction2DSimple.h"

namespace
{
double testResolutionFunction(double u, double v)
{
    double sigma_u = 0.001;
    double sigma_v = 0.001;
    return MathFunctions::IntegratedGaussian(u, 0.0, sigma_u)
            * MathFunctions::IntegratedGaussian(v, 0.0, sigma_v);
}
}

TestDetectorResolution::TestDetectorResolution()
: mp_intensity_output(0)
, mp_sample(0)
{
}

TestDetectorResolution::~TestDetectorResolution()
{
    delete mp_intensity_output;
    delete mp_sample;
}

void TestDetectorResolution::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    initializeSample();
    GISASExperiment experiment(mp_options);
    experiment.setSample(*mp_sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree
            ,100, 0.0*Units::degree, 2.0*Units::degree);
    IResolutionFunction2D *p_resolution_function = new ResolutionFunction2DSimple(0.001, 0.001);
    experiment.setDetectorResolutionFunction(p_resolution_function);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    mp_intensity_output = experiment.getOutputDataClone();
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_detector_resolution", "Detector resolution",
            "CONT4 Z", "Detector resolution");
}

void TestDetectorResolution::initializeSample()
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
    ParticleDecoration particle_decoration(
                new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}
