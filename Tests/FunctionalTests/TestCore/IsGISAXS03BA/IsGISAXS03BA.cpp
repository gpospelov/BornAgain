#include "IsGISAXS03BA.h"
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


FunctionalTests::IsGISAXS03BA::IsGISAXS03BA()
    : m_name("IsGISAXS03BA")
    , m_description("Cylinders in BA")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS03BA::run(const std::string &path_to_data)
{

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs03_ba");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs03_reference_BA.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int FunctionalTests::IsGISAXS03BA::analyseResults()
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
    FunctionalTests::IsGISAXS03BA test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif
