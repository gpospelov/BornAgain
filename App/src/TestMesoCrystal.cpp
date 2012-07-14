#include "TestMesoCrystal.h"
#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "LayerDecorator.h"
#include "NanoParticleDecoration.h"
#include "MesoCrystal.h"
#include "NanoParticleCrystal.h"
#include "FormFactors.h"


TestMesoCrystal::TestMesoCrystal()
: mp_intensity_output(0)
, mp_sample(0)
{
}

TestMesoCrystal::~TestMesoCrystal()
{
    delete mp_intensity_output;
    delete mp_sample;
}

void TestMesoCrystal::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    initializeSample();
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(0.0*Units::degree, 2.0*Units::degree, 100
            , 0.0*Units::degree, 2.0*Units::degree, 100);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    mp_intensity_output = experiment.getOutputData();
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_meso_crystal", "mesocrystal towers",
            "CONT4 Z");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, "./Examples/mesocrystal.ima");
}

void TestMesoCrystal::initializeSample()
{
    delete mp_sample;
    // create mesocrystal
    double R = 5*Units::nanometer;
    Lattice lat = Lattice::createFCCLattice(R*2.0*std::sqrt(2.0));
    complex_t n_particle(1.0-5e-5, 2e-8);
    NanoParticle particle(n_particle, new FormFactorFullSphere(R));
    NanoParticleCrystal npc(particle, lat);
    MesoCrystal meso(npc.clone(), new FormFactorCylinder(0.5*Units::micrometer, 100*Units::nanometer));

    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-5e-6, 2e-8);

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
//    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(400.0*Units::nanometer,
//            1*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(meso.clone());
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}
