#include "IsGISAXS07.h"
#include "Rotate3D.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "FormFactorBox.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "OutputDataIOFactory.h"
#include "PositionParticleInfo.h"
#include "Utils.h"
#include "Units.h"
#include "MathFunctions.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"
#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS07::IsGISAXS07()
    : m_name("IsGISAXS07")
    , m_description("Mixture of different particles defined in morphology file")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS07::run(const std::string &path_to_data)
{
	SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs07");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs07_reference.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}

int FunctionalTests::IsGISAXS07::analyseResults()
{
    const double threshold(2e-10);

    // calculating average relative difference
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
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
    FunctionalTests::IsGISAXS07 test;
    test.run(GetPathToData(argc, argv));

    return test.analyseResults();
}
#endif
