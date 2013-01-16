#include "IsGISAXS01.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "GISASExperiment.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS01::IsGISAXS01()
    : m_name("IsGISAXS01")
    , m_description("Mixture of cylinders and prisms without interference")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS01::run()
{
    // ---------------------
    // building sample
    // ---------------------
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    ParticleDecoration particle_decoration;
    complex_t n_particle(1.0-6e-4, 2e-8);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // ---------------------
    // building experiment
    // ---------------------
    GISASExperiment experiment;
    experiment.setDetectorParameters(100,-1.0*Units::degree, 1.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running experiment
    // ---------------------
    experiment.setSample(multi_layer);
    experiment.runSimulation();

    // ---------------------
    // copying data
    // ---------------------
    m_result = experiment.getOutputDataClone();

}


int FunctionalTests::IsGISAXS01::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data
    std::string filename = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS01/isgisaxs01_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS01 test;
    test.run();

    return test.analyseResults();
}
#endif
