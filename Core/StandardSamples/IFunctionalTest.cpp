#include "IFunctionalTest.h"
#include "SimulationRegistry.h"
#include "OutputDataIOFactory.h"
#include "OutputDataFunctions.h"
#include "FileSystem.h"


void FunctionalTest::runTest()
{
    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation(getName());

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + m_info.m_reference_file;
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();
    m_result = simulation->getIntensityData();
    delete simulation;
}

int FunctionalTest::analyseResults()
{
    assert(m_result);
    assert(m_reference);
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    std::cout << getName() << " " << getDescription() << " " << diff
              << " " << (diff>m_info.m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > m_info.m_threshold ) return FAILED;
    return SUCCESS;
}
