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
#include "LatticeBasis.h"
#include "MathFunctions.h"
#include "Utils.h"


namespace
{
double testResolutionFunction(double u, double v)
{
    double sigma_u = 0.0002;
    double sigma_v = 0.0002;
    return MathFunctions::IntegratedGaussian(u, 0.0, sigma_u)
            * MathFunctions::IntegratedGaussian(v, 0.0, sigma_v);
}
}

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
    experiment.setDetectorParameters(100, 0.3*Units::degree, 0.073
           , 100 , -0.4*Units::degree, 0.066);
//    experiment.setDetectorResolutionFunction(&testResolutionFunction);
    experiment.setBeamParameters(1.54*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    experiment.setBeamIntensity(1e3);
    experiment.runSimulation();
    experiment.normalize();
    mp_intensity_output = experiment.getOutputDataClone();
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_meso_crystal", "mesocrystal",
            "CONT4 Z");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/MesoCrystals/mesocrystal.ima");
}

void TestMesoCrystal::initializeSample()
{
    delete mp_sample;
    // create mesocrystal
    double R = 6.1*Units::nanometer;
    double meso_radius = 300*Units::nanometer;
    double surface_filling_ratio = 0.25;
    double surface_density = surface_filling_ratio/M_PI/meso_radius/meso_radius;
    Lattice lat = Lattice::createTrigonalLattice(R*2.0, R*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    complex_t n_particle(1.0-1.55e-5, 1.37e-6);
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(surface_filling_ratio*avg_n_squared_meso + 1.0 - surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    NanoParticle particle(n_particle_adapted, new FormFactorFullSphere(R));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    NanoParticleCrystal npc(basis, lat);
    MesoCrystal meso(npc.clone(), new FormFactorCylinder(0.2*Units::micrometer, meso_radius));
    MesoCrystal meso2(npc.clone(), new FormFactorPyramid(0.2*Units::micrometer, meso_radius, 84*Units::degree));

    // Create multilayer
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-7.57e-6, 1.73e-7);

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_average_layer_material = MaterialManager::instance().addHomogeneousMaterial("Averagelayer", n_avg);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer avg_layer;
    avg_layer.setMaterial(p_average_layer_material);
    avg_layer.setThickness(0.2*Units::micrometer);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
//    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(800.0*Units::nanometer,
//            50*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration;
    size_t n_phi_rotation_steps = 11;
    size_t n_alpha_rotation_steps =3;
    double phi_step = 2*M_PI/3.0/n_phi_rotation_steps;
    double alpha_step = 5*Units::degree/n_alpha_rotation_steps;
    for (size_t i=0; i<n_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
            Geometry::RotateZ3D transform1(i*phi_step);
            Geometry::RotateY3D transform2(j*alpha_step);
            particle_decoration.addNanoParticle(meso, transform1*transform2, 0.2*Units::micrometer, 0.5);
//            particle_decoration.addNanoParticle(meso2, transform1, 0.2*Units::micrometer, 0.5);
        }
    }
    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator avg_layer_decorator(avg_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}
