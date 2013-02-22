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
    , m_result(0)
{}

//-----------------------------------------------------
//IsGISAXS6_lattice()
//-----------------------------------------------------
void FunctionalTests::IsGISAXS06::runlattice()
{
    // ---------------------
    // building sample
    // ---------------------
        MultiLayer multi_layer;
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        Lattice2DIFParameters lattice_params = {
                10.0*Units::nanometer,       // L1
                10.0*Units::nanometer,       // L2
                90.0*Units::degree,          // lattice angle
                0.0*Units::degree,           // lattice orientation
                20000.0*Units::nanometer,    // domain size 1
                20000.0*Units::nanometer,    // domain size 2
                300.0*Units::nanometer/2.0/M_PI, // correlation length 1
                100.0*Units::nanometer/2.0/M_PI  // correlation length 2
        };
        InterferenceFunction2DLattice *p_interference_function = new InterferenceFunction2DLattice(lattice_params);
        FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
        p_interference_function->setProbabilityDistribution(pdf);

        ParticleDecoration particle_decoration;
        // particle
        FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
        kvector_t position(0.0, 0.0, 0.0);
        PositionParticleInfo particle_info( new Particle(n_particle, ff_cyl.clone()), 0, position, 1.0);
        particle_decoration.addParticleInfo(particle_info);

        particle_decoration.addInterferenceFunction(p_interference_function);
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer.addLayer(air_layer_decorator);
        multi_layer.addLayer(substrate_layer);
        // ---------------------
        // building simulation
        // ---------------------
        Simulation simulation;
        simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

        SimulationParameters sim_params;
        sim_params.me_framework = SimulationParameters::DWBA;
        sim_params.me_if_approx = SimulationParameters::LMA;
        sim_params.me_lattice_type = SimulationParameters::LATTICE;
        simulation.setSimulationParameters(sim_params);

        // ---------------------
        // running simulation and copying data
        // ---------------------
        simulation.setSample(multi_layer);
        simulation.runSimulation();
        m_result = simulation.getOutputDataClone();
        OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),"this_lattice.ima");
 }

//-----------------------------------------------------
// IsGISAXS6 functional test: cylinders lattice centered
//-----------------------------------------------------
void FunctionalTests::IsGISAXS06::runcentered()
{
    // ---------------------
    // building sample
    // ---------------------
        MultiLayer multi_layer;
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air",  1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        Lattice2DIFParameters lattice_params = {
                10.0*Units::nanometer,       // L1
                10.0*Units::nanometer,       // L2
                90.0*Units::degree,          // lattice angle
                0.0*Units::degree,           // lattice orientation
                20000.0*Units::nanometer,    // domain size 1
                20000.0*Units::nanometer,    // domain size 2
                300.0*Units::nanometer/2.0/M_PI, // correlation length 1
                100.0*Units::nanometer/2.0/M_PI  // correlation length 2
        };
        InterferenceFunction2DLattice *p_interference_function = new InterferenceFunction2DLattice(lattice_params);
        FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
        p_interference_function->setProbabilityDistribution(pdf);

        ParticleDecoration particle_decoration;
        // particle 1
        FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
        kvector_t position(0.0, 0.0, 0.0);
        PositionParticleInfo particle_info( new Particle(n_particle, ff_cyl.clone()), 0, position, 1.0);
        particle_decoration.addParticleInfo(particle_info);
        // particle 2
        kvector_t position_2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
        particle_info.setPosition(position_2);
        particle_decoration.addParticleInfo(particle_info);

        particle_decoration.addInterferenceFunction(p_interference_function);
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer.addLayer(air_layer_decorator);
        multi_layer.addLayer(substrate_layer);

        // ---------------------
        // building simulation
        // ---------------------
        Simulation simulation;
        simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

        SimulationParameters sim_params;
        sim_params.me_framework = SimulationParameters::DWBA;
        sim_params.me_if_approx = SimulationParameters::LMA;
        sim_params.me_lattice_type = SimulationParameters::LATTICE;
        simulation.setSimulationParameters(sim_params);

        // ---------------------
        // running simulation and copying data
        // ---------------------
        simulation.setSample(multi_layer);
        simulation.runSimulation();
        m_result = simulation.getOutputDataClone();
        OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),"this_centered.ima");
}

//-----------------------------------------------------
// IsGISAXS6 functional test: cylinders lattice rotated
//-----------------------------------------------------
void FunctionalTests::IsGISAXS06::runrotated()
{
        MultiLayer multi_layer;
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        Lattice2DIFParameters lattice_params = {
                10.0*Units::nanometer,       // L1
                10.0*Units::nanometer,       // L2
                90.0*Units::degree,          // lattice angle
                30.0*Units::degree,           // lattice orientation
                20000.0*Units::nanometer,    // domain size 1
                20000.0*Units::nanometer,    // domain size 2
                300.0*Units::nanometer/2.0/M_PI, // correlation length 1
                100.0*Units::nanometer/2.0/M_PI  // correlation length 2
        };
        InterferenceFunction2DLattice *p_interference_function = new InterferenceFunction2DLattice(lattice_params);
        FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
        pdf.setGamma(30.0*Units::degree);
        p_interference_function->setProbabilityDistribution(pdf);

        ParticleDecoration particle_decoration;
        // particle
        FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
        kvector_t position(0.0, 0.0, 0.0);
        PositionParticleInfo particle_info( new Particle(n_particle, ff_cyl.clone()), 0, position, 1.0);
        particle_decoration.addParticleInfo(particle_info);
        particle_decoration.addInterferenceFunction(p_interference_function);
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer.addLayer(air_layer_decorator);
        multi_layer.addLayer(substrate_layer);

        // ---------------------
        // building simulation
        // ---------------------
        Simulation simulation;
        simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

        SimulationParameters sim_params;
        sim_params.me_framework = SimulationParameters::DWBA;
        sim_params.me_if_approx = SimulationParameters::LMA;
        sim_params.me_lattice_type = SimulationParameters::LATTICE;
        simulation.setSimulationParameters(sim_params);

        // ---------------------
        // running simulation and copying data
        // ---------------------
        simulation.setSample(multi_layer);
        simulation.runSimulation();
        m_result = simulation.getOutputDataClone();
        OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),"this_rotated.ima");
}

//-----------------------------------------------------
// lattice variants
//-----------------------------------------------------
void FunctionalTests::IsGISAXS06::runvariants()
{
    // ---------------------
    // building simulation
    // ---------------------
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    simulation.setSimulationParameters(sim_params);

    // ---------------------
    // running simulation and copying data
    // ---------------------
    OutputData<double> *p_total = simulation.getOutputDataClone();
    p_total->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticSampledParameter xi(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max);
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

    OutputDataIOFactory::writeOutputData(*p_total,"this_variants.ima");
    m_result = OutputDataIOFactory::getOutputData("this_variants.ima");
    delete p_total;
}

// IsGISAXS6 functional test sample builder for varying xi angle
ISample* FunctionalTests::IsGISAXS06::LatticeVariantBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0,0.0);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    Lattice2DIFParameters lattice_params = {
            10.0*Units::nanometer,       // L1
            10.0*Units::nanometer,       // L2
            90.0*Units::degree,          // lattice angle
            m_xi,           // lattice orientation
            20000.0*Units::nanometer,    // domain size 1
            20000.0*Units::nanometer,    // domain size 2
            300.0*Units::nanometer/2.0/M_PI, // correlation length 1
            100.0*Units::nanometer/2.0/M_PI  // correlation length 2
    };
    InterferenceFunction2DLattice *p_interference_function = new InterferenceFunction2DLattice(lattice_params);
    FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
    p_interference_function->setProbabilityDistribution(pdf);

    ParticleDecoration particle_decoration;
    // particle
    FormFactorCylinder ff_cyl(5.0*Units::nanometer, 5.0*Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    PositionParticleInfo particle_info( new Particle(n_particle, ff_cyl.clone()), 0, position, 1.0);
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

    std::vector< CompareStruct > tocompare;

    tocompare.push_back( CompareStruct("isgisaxs06_reference_lattice.ima.gz",      "this_lattice.ima",      "Cylinder 2D lattice") );
    tocompare.push_back( CompareStruct("isgisaxs06_reference_centered.ima.gz",     "this_centered.ima",      "Cylinder 2D lattice centered") );
    tocompare.push_back( CompareStruct("isgisaxs06_reference_rotated.ima.gz",      "this_rotated.ima",      "Cylinder 2D lattice rotated") );
    tocompare.push_back( CompareStruct("isgisaxs06_reference_variants.ima.gz",     "this_variants.ima",      "Cylinder 2D lattice variants") );

    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].isginame);
        OutputData<double> *m_result = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].thisname);
        std::string descript  = tocompare[i].descr;

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();
    if( diff > threshold ) status_ok=false;

    std::cout << descript << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS06 test;
    //test.run();
    test.runlattice();
    test.runcentered();
    test.runrotated();
    test.runvariants();

    return test.analyseResults();
}
#endif

