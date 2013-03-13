#include "IsGISAXS08.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS08::IsGISAXS08()
    : m_name("IsGISAXS08")
    , m_description("2DDL paracrystal")
    , m_path(Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS08/")
{
    m_results.resize(kNumberOfTests, 0);
}


FunctionalTests::IsGISAXS08::~IsGISAXS08()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) delete (*it);
}


// IsGISAXS8 functional test: 2DDL lattice
void FunctionalTests::IsGISAXS08::run2DDL()
{
    // building sample
    MultiLayer multi_layer;
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 2.0*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 2.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    simulation.setSample(multi_layer);

    // running simulation and copying data
    simulation.runSimulation();
    m_results[kTest_2DDL] = simulation.getOutputDataClone();
}


// IsGISAXS8 functional test: 2D paracrystal lattice with isotropic pdfs
void FunctionalTests::IsGISAXS08::run2DDL2()
{
    // building sample
    MultiLayer multi_layer;
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 0.5*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 0.5*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_2DDL2] = simulation.getOutputDataClone();
}


int FunctionalTests::IsGISAXS08::analyseResults()
{
    const double threshold(1e-10);
    const char *reference_files[kNumberOfTests] = {"isgisaxs08_reference_2DDL_lattice.ima.gz", "isgisaxs08_reference_2DDL_lattice2.ima.gz"};
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(m_path + reference_files[i_test]);
        OutputData<double> *result = m_results[i_test];

        // calculating average relative difference
        *result -= *reference;
        *result /= *reference;
        double diff(0);
        for(OutputData<double>::const_iterator it=result->begin(); it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= result->getAllocatedSize();
        if( diff > threshold || std::isnan(diff)) status_ok=false;
        delete reference;
    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;

}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS08 test;
    test.run2DDL();
    test.run2DDL2();
    return test.analyseResults();
}
#endif



