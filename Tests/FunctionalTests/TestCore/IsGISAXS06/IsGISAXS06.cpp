#include "IsGISAXS06.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "Units.h"
#include "MaterialManager.h"
#include "InterferenceFunction2DLattice.h"
#include "PositionParticleInfo.h"
#include "OutputDataIOFactory.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS06::IsGISAXS06()
    : m_name("IsGISAXS06")
    , m_description("2D lattice with different disorder")
    , m_path(Utils::FileSystem::GetHomePath() +
             "Tests/FunctionalTests/TestCore/IsGISAXS06/")
{
    m_results.resize(kNumberOfTests, 0);
}


FunctionalTests::IsGISAXS06::~IsGISAXS06()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) delete (*it);
}


// IsGISAXS6_lattice()
void FunctionalTests::IsGISAXS06::runlattice()
{
    // building sample
    MultiLayer multi_layer;
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = 0.0*Units::degree; // lattice orientation
    // domain sizes
    lattice_params.m_domain_size_1 = 20000.0*Units::nanometer;
    lattice_params.m_domain_size_2 = 20000.0*Units::nanometer;
    // correlation lengths
    lattice_params.m_corr_length_1 = 300.0*Units::nanometer/2.0/M_PI;
    lattice_params.m_corr_length_2 = 100.0*Units::nanometer/2.0/M_PI;

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    // particles
    ParticleDecoration particle_decoration;
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(n_particle, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation.setSimulationParameters(sim_params);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_Lattice] = simulation.getOutputDataClone();
}


// IsGISAXS6 functional test: cylinders lattice centered
void FunctionalTests::IsGISAXS06::runcentered()
{
    // building sample
    MultiLayer multi_layer;
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air",  1.0, 0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = 0.0*Units::degree; // lattice orientation
    lattice_params.m_domain_size_1 = 20000.0*Units::nanometer; // domain size 1
    lattice_params.m_domain_size_2 =20000.0*Units::nanometer; // domain size 2
    lattice_params.m_corr_length_1 = 300.0*Units::nanometer/2.0/M_PI; // correlation length 1
    lattice_params.m_corr_length_2 = 100.0*Units::nanometer/2.0/M_PI;  // correlation length 2

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleDecoration particle_decoration;
    // particle 1
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(n_particle, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);
    // particle 2
    kvector_t position_2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    particle_info.setPosition(position_2);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation.setSimulationParameters(sim_params);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_Centered] = simulation.getOutputDataClone();
}


// IsGISAXS6 functional test: cylinders lattice rotated
void FunctionalTests::IsGISAXS06::runrotated()
{
    MultiLayer multi_layer;
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = 30.0*Units::degree; // lattice orientation
    // domain sizes:
    lattice_params.m_domain_size_1 = 20000.0*Units::nanometer;
    lattice_params.m_domain_size_2 = 20000.0*Units::nanometer;
    // correlation lengths:
    lattice_params.m_corr_length_1 = 300.0*Units::nanometer/2.0/M_PI;
    lattice_params.m_corr_length_2 = 100.0*Units::nanometer/2.0/M_PI;

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    pdf.setGamma(30.0*Units::degree);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleDecoration particle_decoration;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(n_particle, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom,
                                -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation.setSimulationParameters(sim_params);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_Rotated] = simulation.getOutputDataClone();
}


// lattice variants
void FunctionalTests::IsGISAXS06::runvariants()
{
    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom,
                                -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation.setSimulationParameters(sim_params);

    // running simulation and copying data
    OutputData<double> *p_total = simulation.getOutputDataClone();
    p_total->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticDoubleGate xg(xi_min, xi_max);
    StochasticSampledParameter xi(xg, nbins, xi_min, xi_max);
    for (size_t i=0; i<xi.getNbins(); ++i) {
        double xi_value = xi.getBinValue(i);
        double probability = xi.getNormalizedProbability(i);
        m_builder.setXi(xi_value);
        MultiLayer *p_sample = dynamic_cast<MultiLayer *>(m_builder.buildSample());
        simulation.setSample(*p_sample);
        simulation.runSimulation();
        delete p_sample;
        OutputData<double> *p_single_output = simulation.getOutputDataClone();
        p_single_output->scaleAll(probability);
        *p_total += *p_single_output;
        delete p_single_output;
    }

    m_results[kTest_Variants] = p_total;
}

// IsGISAXS6 functional test sample builder for varying xi angle
ISample* FunctionalTests::IsGISAXS06::LatticeVariantBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
         MaterialManager::getHomogeneousMaterial("Air", 1.0,0.0);
    const IMaterial *p_substrate_material =
         MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    Lattice2DIFParameters lattice_params;
    lattice_params.m_length_1 = 10.0*Units::nanometer; // L1
    lattice_params.m_length_2 = 10.0*Units::nanometer; // L2
    lattice_params.m_angle = 90.0*Units::degree; // lattice angle
    lattice_params.m_xi = m_xi; // lattice orientation
    lattice_params.m_domain_size_1 = 20000.0*Units::nanometer;
    lattice_params.m_domain_size_2 = 20000.0*Units::nanometer;
    lattice_params.m_corr_length_1 = 300.0*Units::nanometer/2.0/M_PI;
    lattice_params.m_corr_length_2 = 100.0*Units::nanometer/2.0/M_PI;

    InterferenceFunction2DLattice *p_interference_function =
        new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI,
                               100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleDecoration particle_decoration;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info(
        new Particle(n_particle, ff_cyl.clone()), position, 1.0);
    particle_decoration.addParticleInfo(particle_info);

    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


int FunctionalTests::IsGISAXS06::analyseResults()
{
    const double threshold(1e-10);
    const char *reference_files[kNumberOfTests] = {
        "isgisaxs06_reference_lattice.ima.gz",
        "isgisaxs06_reference_centered.ima.gz",
        "isgisaxs06_reference_rotated.ima.gz",
        "isgisaxs06_reference_variants.ima.gz"
    };
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference =
            OutputDataIOFactory::getOutputData(m_path + reference_files[i_test]);
        OutputData<double> *result = m_results[i_test];

        // calculating average relative difference
        *result -= *reference;
        *result /= *reference;
        delete reference;

        double diff(0);
        for(OutputData<double>::const_iterator it =
                result->begin(); it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= result->getAllocatedSize();
        if( diff > threshold || std::isnan(diff)) status_ok=false;
    }

    std::cout << m_name << " " << m_description << " " <<
        (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS06 test;
    test.runlattice();
    test.runcentered();
    test.runrotated();
    test.runvariants();

    return test.analyseResults();
}
#endif

