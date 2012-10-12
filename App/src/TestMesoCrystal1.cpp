#include "TestMesoCrystal1.h"
#include "IsGISAXSTools.h"
#include "Types.h"
#include "Units.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "MesoCrystal.h"
#include "Crystal.h"
#include "FormFactors.h"
#include "LatticeBasis.h"
#include "MathFunctions.h"
#include "Utils.h"
#include "FormFactorDecoratorDebyeWaller.h"

/* ************************************************************************* */
// global functions
/* ************************************************************************* */
namespace {
    double testResolutionFunction(double u, double v)
    {
        double sigma_u = 0.0002;
        double sigma_v = 0.0002;
        return MathFunctions::IntegratedGaussian(u, 0.0, sigma_u)
                * MathFunctions::IntegratedGaussian(v, 0.0, sigma_v);
    }
}

/* ************************************************************************* */
// TestMesoCrystal1 member definitions
/* ************************************************************************* */
TestMesoCrystal1::TestMesoCrystal1()
: mp_intensity_output(0)
, mp_sample_builder(0)
{
    mp_sample_builder = new MesoCrystalBuilder;
}

TestMesoCrystal1::~TestMesoCrystal1()
{
    delete mp_intensity_output;
    delete mp_sample_builder;
}

void TestMesoCrystal1::execute()
{
    if (mp_intensity_output) delete mp_intensity_output;
    GISASExperiment experiment;
    experiment.setSampleBuilder(mp_sample_builder);
    experiment.setDetectorParameters(200, 0.3*Units::degree, 0.073
           , 200, -0.4*Units::degree, 0.066);
//    experiment.setDetectorParameters(2, 0.96*Units::degree, 0.962*Units::degree
//           , 2 , 0.376*Units::degree, 0.378*Units::degree);
//    experiment.setDetectorResolutionFunction(&testResolutionFunction);
    experiment.setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    experiment.setBeamIntensity(8e12);

    ParameterPool *p_param_pool = experiment.createParameterTree();
    std::cout << (*p_param_pool) << std::endl;

    experiment.runSimulation();
    double count_before_normalize = experiment.getOutputData()->total();
    experiment.normalize();
    mp_intensity_output = experiment.getOutputDataClone();
    double total_count = mp_intensity_output->total();
    std::cout << "Total count in detector: " << total_count << std::endl;
    std::cout << "Scattered percentage in detector: " << 100*total_count/experiment.getBeam().getIntensity() << std::endl;
    std::cout << "Total count in detector before normalize: " << count_before_normalize << std::endl;
    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_meso_crystal", "mesocrystal",
            "CONT4 Z", "mesocrystal");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/MesoCrystals/ex01_spheres/mesocrystal.ima");
}

/* ************************************************************************* */
// MesoCrystalBuilder member definitions
/* ************************************************************************* */
MesoCrystalBuilder::MesoCrystalBuilder()
: m_meso_radius(1000*Units::nanometer)
, m_surface_filling_ratio(0.25)
, m_meso_height(0.5*Units::micrometer)
, m_sigma_meso_height(4*Units::nanometer)
, m_sigma_meso_radius(50*Units::nanometer)
, m_lattice_length_a(4.7*Units::nanometer)
, m_nanoparticle_radius(4.2*Units::nanometer)
, m_sigma_nanoparticle_radius(0.2*Units::nanometer)
{
    init_parameters();
}

MesoCrystalBuilder::~MesoCrystalBuilder()
{
}

ISample* MesoCrystalBuilder::buildSample() const
{
    // create mesocrystal
    double surface_density = m_surface_filling_ratio/M_PI/m_meso_radius/m_meso_radius;
//    complex_t n_particle(1.0-1.55e-5, 1.37e-6); // data from Artur
    complex_t n_particle(1.0-2.84e-5, 4.7e-7); // data from http://henke.lbl.gov/optical_constants/getdb2.html
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(m_surface_filling_ratio*avg_n_squared_meso + 1.0 - m_surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    FormFactorCylinder ff_cyl(m_meso_height, m_meso_radius);
    FormFactorDecoratorDebyeWaller ff_meso(ff_cyl.clone(), m_sigma_meso_height*m_sigma_meso_height/2.0,
            m_sigma_meso_radius*m_sigma_meso_radius/2.0);

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
    avg_layer.setThickness(m_meso_height);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
    ParticleDecoration particle_decoration;
    size_t n_max_phi_rotation_steps = 180;
    size_t n_alpha_rotation_steps = 1;

    double alpha_step = 5.0*Units::degree/n_alpha_rotation_steps;
    double alpha_start = - (n_alpha_rotation_steps/2.0)*alpha_step;

    double phi_step = 2.0*M_PI/3.0/n_max_phi_rotation_steps;
    double phi_start = 0.0;
    for (size_t i=0; i<n_max_phi_rotation_steps; ++i) {
        for (size_t j=0; j<n_alpha_rotation_steps; ++j) {
            Geometry::RotateZ3D transform1(phi_start + (double)i*phi_step);
            Geometry::RotateY3D transform2(alpha_start + j*alpha_step);
            Geometry::Transform3D *p_total_transform = new Geometry::Transform3D(transform1);
            particle_decoration.addParticle(createMesoCrystal(m_lattice_length_a,
                    n_particle_adapted, &ff_meso), p_total_transform, m_meso_height);
        }
    }

    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator avg_layer_decorator(avg_layer, particle_decoration);

    LayerRoughness roughness(1.0*Units::nanometer, 0.3, 500.0*Units::nanometer);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer_decorator);
    p_multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);

    std::cout << "Average layer index: " << n_avg << std::endl;
    std::cout << "Adapted particle index: " << n_particle_adapted << std::endl;
    std::cout << "Substrate layer index: " << n_substrate << std::endl;

    return p_multi_layer;
}

void MesoCrystalBuilder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("meso_radius", &m_meso_radius);
    getParameterPool()->registerParameter("surface_filling_ratio", &m_surface_filling_ratio);
    getParameterPool()->registerParameter("meso_height", &m_meso_height);
    getParameterPool()->registerParameter("sigma_meso_height", &m_sigma_meso_height);
    getParameterPool()->registerParameter("sigma_meso_radius", &m_sigma_meso_radius);
    getParameterPool()->registerParameter("lattice_length_a", &m_lattice_length_a);
    getParameterPool()->registerParameter("nanoparticle_radius", &m_nanoparticle_radius);
    getParameterPool()->registerParameter("sigma_nanoparticle_radius", &m_sigma_nanoparticle_radius);
}

MesoCrystal* MesoCrystalBuilder::createMesoCrystal(double stacking_radius, complex_t n_particle,
        const IFormFactor* p_meso_form_factor) const
{
    const Lattice *p_lat = createLattice(stacking_radius);
    kvector_t bas_a = p_lat->getBasisVectorA();
    kvector_t bas_b = p_lat->getBasisVectorB();
    kvector_t bas_c = p_lat->getBasisVectorC();
    Particle particle(n_particle, new FormFactorSphereGaussianRadius(m_nanoparticle_radius, m_sigma_nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);

    Crystal npc(basis, *p_lat);
//    double relative_sigma_np_radius = 0.3;
//    double dw_factor = relative_sigma_np_radius*relative_sigma_np_radius*stacking_radius*stacking_radius/6.0;
//    npc.setDWFactor(dw_factor);
    return new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
}

const Lattice *MesoCrystalBuilder::createLattice(double stacking_radius) const
{
    Lattice *p_result = new Lattice(Lattice::createTrigonalLattice(stacking_radius*2.0, stacking_radius*2.0*2.3));
    p_result->setSelectionRule(new SimpleSelectionRule(-1, 1, 1, 3));
    return p_result;
}


