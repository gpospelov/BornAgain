#include "IsGISAXS03.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunctionNone.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "OutputDataIOFactory.h"
#include "ParticleBuilder.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Units.h"
#include "Utils.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS03::IsGISAXS03()
    : m_name("IsGISAXS03")
    , m_description("Cylinder formfactor in BA and DWBA")
    , m_path(Utils::FileSystem::GetHomePath()+std::string("Tests/FunctionalTests/TestCore/IsGISAXS03/"))
{
    m_results.resize(kNumberOfTests, 0);
}

FunctionalTests::IsGISAXS03::~IsGISAXS03()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) delete (*it);
}


// IsGISAXS3 functional test: cylinder on the substrate
void FunctionalTests::IsGISAXS03::runDWBA()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_DWBA] = simulation.getOutputDataClone();
}


// IsGISAXS3 functional test: cylinder in the air
void FunctionalTests::IsGISAXS03::runBA()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer.addLayer(air_layer_decorator);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_BA] = simulation.getOutputDataClone();
}


// IsGISAXS3 functional test: cylinder in the air with size distribution
void FunctionalTests::IsGISAXS03::runBA_Size()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration;
    // preparing prototype of nano particle
    double radius = 5*Units::nanometer;
    double sigma = 0.2*radius;
    FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( 5*Units::nanometer, radius);
    Particle nano_particle(n_particle, p_ff_cylinder);
    // radius of nanoparticles will be sampled with gaussian probability
    int nbins(100), nfwhm(2);
    StochasticDoubleGaussian double_gaussian(radius, sigma);
    StochasticSampledParameter par(double_gaussian, nbins, nfwhm);
    ParticleBuilder builder;
    builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
    builder.plantParticles(particle_decoration);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer.addLayer(air_layer_decorator);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_results[kTest_BASize] = simulation.getOutputDataClone();
}


int FunctionalTests::IsGISAXS03::analyseResults()
{
    const double threshold(1e-10);
    const char *reference_files[kNumberOfTests] = {"isgisaxs03_reference_DWBA.ima.gz", "isgisaxs03_reference_BA.ima.gz", "isgisaxs03_reference_BA_size.ima.gz"};
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(m_path + reference_files[i_test]);
        OutputData<double> *result = m_results[i_test];

        // calculating average relative difference
        *result -= *reference;
        *result /= *reference;
        delete reference;

        double diff(0);
        for(OutputData<double>::const_iterator it=result->begin(); it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= result->getAllocatedSize();
        if( diff > threshold || std::isnan(diff)) status_ok=false;

    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS03 test;
    test.runDWBA();
    test.runBA();
    test.runBA_Size();
    return test.analyseResults();
}
#endif


