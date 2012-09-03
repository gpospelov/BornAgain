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
//    experiment.setDetectorParameters(5, 2*Units::degree, 3*Units::degree
//           , 5 , 1*Units::degree, 2*Units::degree);
//    experiment.setDetectorResolutionFunction(&testResolutionFunction);
    experiment.setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    experiment.setBeamIntensity(1e7);
    experiment.runSimulation();
    double count_before_normalize = experiment.getOutputData()->total();
    experiment.normalize();
    mp_intensity_output = experiment.getOutputDataClone();
    double total_count = mp_intensity_output->total();
    std::cout << "Total count in detector: " << total_count << std::endl;
    std::cout << "Scattered percentage in detector: " << 100*total_count/experiment.getBeam().getIntensity() << std::endl;
    std::cout << "Total count in detector before normalize: " << count_before_normalize << std::endl;
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_meso_crystal", "mesocrystal",
            "CONT4 Z");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/MesoCrystals/mesocrystal.ima");
}

void TestMesoCrystal::initializeSample()
{
    delete mp_sample;
    // create mesocrystal
    double meso_radius = 600*Units::nanometer;
    double surface_filling_ratio = 0.25;
    double surface_density = surface_filling_ratio/meso_radius/meso_radius;
    complex_t n_particle(1.0-1.55e-5, 1.37e-6);
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(surface_filling_ratio*avg_n_squared_meso + 1.0 - surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    FormFactorLorentz ff_meso(0.2*Units::micrometer, meso_radius);
//    MesoCrystal meso2(npc.clone(), new FormFactorPyramid(0.2*Units::micrometer, meso_radius, 84*Units::degree));

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
    size_t n_phi_rotation_steps = 13;
    size_t n_alpha_rotation_steps = 5;
    size_t n_np_size_steps = 3;
    double phi_step = 2*M_PI/3.0/n_phi_rotation_steps;
    double phi_start = 0.0;
    double alpha_step = 4*Units::degree/n_alpha_rotation_steps;
    double alpha_start = - (n_alpha_rotation_steps/2)*alpha_step;
    double np_size_step = 0.3*Units::nanometer/n_np_size_steps;
    double np_size_start = 6.1*Units::nanometer - (n_np_size_steps/2)*np_size_step;
    for (size_t i=0; i<n_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
            for (size_t k=0; k<n_np_size_steps; ++k) {
                double R = np_size_start + k*np_size_step;
                Geometry::RotateZ3D transform1(phi_start + i*phi_step);
                Geometry::RotateY3D transform2(alpha_start + j*alpha_step);
                Geometry::Transform3D *p_total_transform = new Geometry::Transform3D(transform1*transform2);
                particle_decoration.addNanoParticle(createMesoCrystal(R, n_particle_adapted, &ff_meso), p_total_transform, 0.2*Units::micrometer);
    //            particle_decoration.addNanoParticle(meso2, transform1, 0.2*Units::micrometer, 0.5);
            }
        }
    }
    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator avg_layer_decorator(avg_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;

    std::cout << "Average layer index: " << n_avg << std::endl;
    std::cout << "Adapted particle index: " << n_particle_adapted << std::endl;
    std::cout << "Substrate layer index: " << n_substrate << std::endl;
}

MesoCrystal* createMesoCrystal(double nanoparticle_radius, complex_t n_particle,
        const IFormFactor* p_meso_form_factor)
{
    Lattice lat = Lattice::createTrigonalLattice(nanoparticle_radius*2.0, nanoparticle_radius*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    NanoParticle particle(n_particle, new FormFactorFullSphere(nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    NanoParticleCrystal npc(basis, lat);
    double relative_sigma_np_radius = 0.15;
    double dw_factor = relative_sigma_np_radius*relative_sigma_np_radius*nanoparticle_radius*nanoparticle_radius/6.0;
    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}
