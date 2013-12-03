#include "IsGISAXS042DDL.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "MathFunctions.h"
#include "SimulationRegistry.h"
#include <iostream>
#include <cmath>
#include <gsl/gsl_errno.h>

FunctionalTests::IsGISAXS042DDL::IsGISAXS042DDL()
    : m_name("IsGISAXS042DDL")
    , m_description("2D Paracrystal")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS042DDL::run(const std::string &path_to_data)
{

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs04_2DDL");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs04_reference_2DDLh.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int FunctionalTests::IsGISAXS042DDL::analyseResults()
{
    const double threshold(2e-10);

    // Calculating average relative difference.
    *m_result -= *m_reference;
    *m_result /= *m_reference;

    double diff(0);
    for(OutputData<double>::const_iterator it =
            m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    // Assess result.
	bool status_ok(true);
    if( diff > threshold || std::isnan(diff)) status_ok=false;

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
    FunctionalTests::IsGISAXS042DDL test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif

