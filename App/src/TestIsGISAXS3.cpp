#include "TestIsGISAXS3.h"
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

TestIsGISAXS3::TestIsGISAXS3()
: mp_intensity_output(0), mp_sample(0)
{
}

TestIsGISAXS3::~TestIsGISAXS3()
{
    delete mp_sample;
    delete mp_intensity_output;
}

void TestIsGISAXS3::execute()
{
    initializeSample();
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(0.0*Units::degree, 2.0*Units::degree, 100
            , 0.0*Units::degree, 2.0*Units::degree, 100, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    if (mp_intensity_output) delete mp_intensity_output;
    mp_intensity_output = experiment.getOutputData();
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_dwba_formfactor", "Cylinder DWBA Formfactor",
            "CONT4 Z");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/dwbacyl.ima");
}

void TestIsGISAXS3::initializeSample()
{
    delete mp_sample;
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
                new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}
