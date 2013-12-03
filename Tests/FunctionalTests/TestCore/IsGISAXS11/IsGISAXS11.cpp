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
#include "MathFunctions.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS11::IsGISAXS11()
    : m_name("IsGISAXS11")
    , m_description("Core shell nanoparticles")
    , m_result(0)
    , m_reference(0)
{

}


void FunctionalTests::IsGISAXS11::run(const std::string &path_to_data)
{
	SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs11");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs11_reference.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int FunctionalTests::IsGISAXS11::analyseResults()
{
    const double threshold(2e-10);

    // calculating average relative difference
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << m_name << " " << m_description << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToData("../../../ReferenceData/BornAgain/", argv[0]);
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS11 test;
    test.run(GetPathToData(argc, argv));

    return test.analyseResults();
}
#endif

