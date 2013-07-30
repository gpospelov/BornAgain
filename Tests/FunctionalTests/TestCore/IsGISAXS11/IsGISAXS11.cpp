#include "IsGISAXS11.h"
#include "FormFactorParallelepiped.h"
#include "InterferenceFunctionNone.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "OutputDataIOFactory.h"
#include "ParticleBuilder.h"
#include "ParticleCoreShell.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS11::IsGISAXS11()
    : m_name("IsGISAXS11")
    , m_description("Core shell nanoparticles")
    , m_result(0)
{

}


void FunctionalTests::IsGISAXS11::run()
{
    // building sample
    MultiLayer multi_layer;

    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);

    const IMaterial *shell_material =
            MaterialManager::getHomogeneousMaterial("Shell", n_particle_shell);
    const IMaterial *core_material =
            MaterialManager::getHomogeneousMaterial("Core", n_particle_core);

    Particle shell_particle(shell_material, new FormFactorParallelepiped(
            8*Units::nanometer, 8*Units::nanometer));
    Particle core_particle(core_material, new FormFactorParallelepiped(
            7*Units::nanometer, 6*Units::nanometer));
    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleDecoration particle_decoration(particle.clone());
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer.addLayer(air_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    simulation.setSample(multi_layer);

    // running simulation and copying data
    simulation.runSimulation();
    m_result = simulation.getOutputDataClone();
}


int FunctionalTests::IsGISAXS11::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);

    // retrieving reference data
    std::string filename = path_to_data + "isgisaxs11_reference.ima.gz";
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
    FunctionalTests::IsGISAXS11 test;
    test.run();

    return test.analyseResults(GetPathToData(argc, argv));
}
#endif

