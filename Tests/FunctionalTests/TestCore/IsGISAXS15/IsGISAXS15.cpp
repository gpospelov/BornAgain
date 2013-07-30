#include "IsGISAXS15.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "ParticleBuilder.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "Units.h"
#include "MaterialManager.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS15::IsGISAXS15()
    : m_name("IsGISAXS15")
    , m_description("Size spacing correlation approximation")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS15::run()
{
    // building sample
    MultiLayer multi_layer;
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    InterferenceFunction1DParaCrystal *p_interference_function =
            new InterferenceFunction1DParaCrystal(15.0*Units::nanometer,
                    5*Units::nanometer, 1e3*Units::nanometer);
    p_interference_function->setKappa(4.02698);
    ParticleDecoration particle_decoration;
    Particle particle_prototype(particle_material, new FormFactorCylinder(
            5.0*Units::nanometer, 5.0*Units::nanometer));
    StochasticDoubleGaussian sg(5.0*Units::nanometer, 1.25*Units::nanometer);
    StochasticSampledParameter stochastic_radius(sg,30, 2);
    ParticleBuilder particle_builder;
    particle_builder.setPrototype(particle_prototype,
            "/Particle/FormFactorCylinder/radius", stochastic_radius);
    particle_builder.plantParticles(particle_decoration);

    // Set height of each particle to its radius (H/R fixed)
    ParameterPool *p_parameters = particle_decoration.createParameterTree();
    p_parameters->fixRatioBetweenParameters("height", "radius", 1.0);

    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setDecoration(particle_decoration);

    multi_layer.addLayer(air_layer);

   // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(150, 0.05*Units::degree, 1.5*Units::degree,
            150, 0.05*Units::degree, 1.5*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    SimulationParameters sim_params;
    sim_params.me_if_approx = SimulationParameters::SSCA;
    simulation.setSimulationParameters(sim_params);
    simulation.setSample(multi_layer);

    // running simulation and copying the data
    simulation.runSimulation();
    m_result = simulation.getOutputDataClone();
}


int FunctionalTests::IsGISAXS15::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);

    // retrieving reference data
    std::string filename = path_to_data + "isgisaxs15_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    delete reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin();
            it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold || std::isnan(diff)) status_ok=false;

    std::cout << m_name << " " << m_description << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToExecutable(argv[0]) +
            "../../../ReferenceData/BornAgain/";
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS15 test;
    test.run();
    return test.analyseResults(GetPathToData(argc, argv));
}
#endif

