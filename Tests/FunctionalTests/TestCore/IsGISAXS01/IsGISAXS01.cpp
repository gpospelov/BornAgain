#include "IsGISAXS01.h"

#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "InterferenceFunctionNone.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "OutputDataIOFactory.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "MessageService.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS01::IsGISAXS01()
    : m_name("IsGISAXS01")
    , m_description("Mixture of cylinders and prisms without interference")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS01::run()
{
    // ------------
    // Build sample
    // ------------
    MultiLayer multi_layer;
    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air", 1., 0.);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate", 1-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    ParticleDecoration particle_decoration;
    complex_t n_particle(1.0-6e-4, 2e-8);
    particle_decoration.addParticle(
        new Particle(n_particle,
                     new FormFactorCylinder(5*Units::nanometer,
                                            5*Units::nanometer)),
        0.0, 0.5);
    particle_decoration.addParticle(
        new Particle(n_particle,
                     new FormFactorPrism3(5*Units::nanometer,
                                          5*Units::nanometer)),
        0.0, 0.5);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // ----------------
    // Build simulation
    // ----------------
    Simulation simulation;
    simulation.setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // --------------
    // Run simulation
    // --------------
    simulation.setSample(multi_layer);
    simulation.runSimulation();

    // ------------
    // Copy results
    // ------------
    m_result = simulation.getOutputDataClone();
}


int FunctionalTests::IsGISAXS01::analyseResults()
{
    const double threshold(1e-10);

    // Retrieve reference data.
    std::string filename =
        Utils::FileSystem::GetHomePath() +
        "/Tests/FunctionalTests/TestCore/IsGISAXS01/isgisaxs01_reference.ima.gz";
    OutputData<double > *reference =
        OutputDataIOFactory::getOutputData(filename);

    // Calculating average relative difference.
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it =
            m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    // Assess result.
    bool status_ok(true);
    if( diff > threshold || std::isnan(diff) ) status_ok=false;
    delete reference;

    std::cout << m_name << " " << m_description << " " <<
        (status_ok ? "[OK]" : "[FAILED]") << std::endl;

    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
int main()
{
    //MSG::SetLevel(MSG::INFO);
    FunctionalTests::IsGISAXS01 test;
    test.run();

    return test.analyseResults();
}
#endif
