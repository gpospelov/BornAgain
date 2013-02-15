#include "IsGISAXS06.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
//#include "InterferenceFunctionNone.h"
#include "FormFactorCylinder.h"
//#include "FormFactorPrism3.h"
//#include "Experiment.h"
#include "Units.h"
#include "MaterialManager.h"
#include "InterferenceFunction2DLattice.h"
#include "PositionParticleInfo.h"
//#include "OutputDataIOFactory.h"
//#include "Utils.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS06::IsGISAXS06()
    : m_name("IsGISAXS06")
    , m_description("2D lattice with different disorder")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS06::run()
{
    // ---------------------
    // building sample
    // ---------------------

    //IsGISAXS6_lattice()

        MultiLayer multi_layer_lattice;

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

        multi_layer_lattice.addLayer(air_layer_decorator);
        multi_layer_lattice.addLayer(substrate_layer);

    // IsGISAXS6 functional test: cylinders lattice centered
        MultiLayer multi_layer_centered;
        Lattice2DIFParameters lattice_params_centered = {
                10.0*Units::nanometer,       // L1
                10.0*Units::nanometer,       // L2
                90.0*Units::degree,          // lattice angle
                0.0*Units::degree,           // lattice orientation
                20000.0*Units::nanometer,    // domain size 1
                20000.0*Units::nanometer,    // domain size 2
                300.0*Units::nanometer/2.0/M_PI, // correlation length 1
                100.0*Units::nanometer/2.0/M_PI  // correlation length 2
        };
        InterferenceFunction2DLattice *p_interference_function_centered = new InterferenceFunction2DLattice(lattice_params_centered);
        p_interference_function_centered->setProbabilityDistribution(pdf);

        ParticleDecoration particle_decoration_centered;
        // particle 1
        particle_decoration_centered.addParticleInfo(particle_info);
        // particle 2
        kvector_t position_2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
        particle_info.setPosition(position_2);
        particle_decoration_centered.addParticleInfo(particle_info);

        particle_decoration_centered.addInterferenceFunction(p_interference_function_centered);
        LayerDecorator air_layer_decorator_centered(air_layer, particle_decoration_centered);

        multi_layer_centered.addLayer(air_layer_decorator_centered);
        multi_layer_centered.addLayer(substrate_layer);

        // IsGISAXS6 functional test: cylinders lattice rotated
        MultiLayer multi_layer_rotated;
        Lattice2DIFParameters lattice_params_rotated = {
                10.0*Units::nanometer,       // L1
                10.0*Units::nanometer,       // L2
                90.0*Units::degree,          // lattice angle
                30.0*Units::degree,           // lattice orientation
                20000.0*Units::nanometer,    // domain size 1
                20000.0*Units::nanometer,    // domain size 2
                300.0*Units::nanometer/2.0/M_PI, // correlation length 1
                100.0*Units::nanometer/2.0/M_PI  // correlation length 2
        };
        InterferenceFunction2DLattice *p_interference_function_rotated = new InterferenceFunction2DLattice(lattice_params_rotated);
       // FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
        pdf.setGamma(30.0*Units::degree);
        p_interference_function_rotated->setProbabilityDistribution(pdf);

        ParticleDecoration particle_decoration_rotated;
        // particle
        particle_decoration_rotated.addParticleInfo(particle_info);
        particle_decoration_rotated.addInterferenceFunction(p_interference_function_rotated);
        LayerDecorator air_layer_decorator_rotated(air_layer, particle_decoration_rotated);

        multi_layer_rotated.addLayer(air_layer_decorator_rotated);
        multi_layer_rotated.addLayer(substrate_layer);

      //  LatticeVariantBuilder

            MultiLayer multi_layer_variant;
            Lattice2DIFParameters lattice_params_variant = {
                    10.0*Units::nanometer,       // L1
                    10.0*Units::nanometer,       // L2
                    90.0*Units::degree,          // lattice angle
                    m_xi,           // lattice orientation
                    20000.0*Units::nanometer,    // domain size 1
                    20000.0*Units::nanometer,    // domain size 2
                    300.0*Units::nanometer/2.0/M_PI, // correlation length 1
                    100.0*Units::nanometer/2.0/M_PI  // correlation length 2
            };
            InterferenceFunction2DLattice *p_interference_function_variant = new InterferenceFunction2DLattice(lattice_params_variant);
            FTDistribution2DCauchy pdf(300.0*Units::nanometer/2.0/M_PI, 100.0*Units::nanometer/2.0/M_PI);
            p_interference_function_variant->setProbabilityDistribution(pdf);

            ParticleDecoration particle_decoration_variant;
            // particle
            particle_decoration_variant.addParticleInfo(particle_info);
            particle_decoration_variant.addInterferenceFunction(p_interference_function);
            LayerDecorator air_layer_decorator_variant(air_layer, particle_decoration_variant);

            multi_layer_variant.addLayer(air_layer_decorator_variant);
            multi_layer_variant.addLayer(substrate_layer);

/*OutputData<double> *p_total = experiment.getOutputDataClone();
    p_total->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticSampledParameter xi(StochasticDoubleGate(xi_min, xi_max), nbins, xi_min, xi_max);
    for (size_t i=0; i<xi.getNbins(); ++i) {
        double xi_value = xi.getBinValue(i);
        double probability = xi.getNormalizedProbability(i);
        m_builder.setXi(xi_value);
        p_sample = dynamic_cast<MultiLayer *>(m_builder.buildSample());
        experiment.setSample(*p_sample);
        experiment.runExperiment();
        delete p_sample;
        OutputData<double> *p_single_output = experiment.getOutputDataClone();
        p_single_output->scaleAll(probability);
        *p_total += *p_single_output;
        delete p_single_output;
    }
    OutputDataIOFactory::writeOutputData(*p_total, m_data_path+"this_variants.ima");
    delete p_total;*/


    // ---------------------
    // building experiment
    // ---------------------
    Experiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    experiment.setSimulationParameters(sim_params);

    // ---------------------
    // running experiment and copying data
    // ---------------------
    // normal lattice
    experiment.setSample(multi_layer_lattice);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_lattice.ima");

     // centered lattice
    experiment.setSample(multi_layer_centered);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_centered.ima");

     // rotated lattice
    experiment.setSample(multi_layer_rotated);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_rotated.ima");

     // lattice variants ??


    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_variants.ima");
}

int FunctionalTests::IsGISAXS06::analyseResults()
{
    const double threshold(1e-10);

    std::vector< CompareStruct > tocompare;
    m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS06/";

    tocompare.push_back( CompareStruct("isgi_lattice.ima.gz",      "this_lattice.ima",      "Cylinder 2D lattice") );
    tocompare.push_back( CompareStruct("isgi_centered.ima.gz",      "this_centered.ima",      "Cylinder 2D lattice centered") );
    tocompare.push_back( CompareStruct("isgi_rotated.ima.gz",      "this_rotated.ima",      "Cylinder 2D lattice rotated") );
    tocompare.push_back( CompareStruct("isgi_variants.ima.gz",      "this_variants.ima",      "Cylinder 2D lattice variants") );


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
    test.run();

    return test.analyseResults();
}
#endif

