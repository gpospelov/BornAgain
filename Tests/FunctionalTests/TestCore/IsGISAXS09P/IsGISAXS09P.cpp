#include "IsGISAXS09P.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Utils.h"
#include "Units.h"
#include "MathFunctions.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS09::IsGISAXS09()
    : m_name("IsGISAXS09")
    , m_description("Pyramids on top of substrate")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS09::run(const std::string &path_to_data)
{

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs09");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs09_reference_pyramid_Z0.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int FunctionalTests::IsGISAXS09::analyseResults()
{
    const double threshold(2e-10);

    // Calculating average relative difference.
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    // Assess result.
	bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
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
    FunctionalTests::IsGISAXS09 test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif
