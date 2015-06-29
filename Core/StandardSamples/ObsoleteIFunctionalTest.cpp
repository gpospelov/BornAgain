#include "ObsoleteIFunctionalTest.h"
#include "SimulationRegistry.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataFunctions.h"
#include "FileSystem.h"
#include <boost/scoped_ptr.hpp>

ObsoleteFunctionalTest::ObsoleteFunctionalTest(const ObsoleteFunctionalTestInfo &info)
    : m_info(info),
      m_simulation(0),
      m_reference(0)
{
    SimulationRegistry sim_registry;
    m_simulation = sim_registry.createSimulation(getName());

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + m_info.m_reference_file;
    m_reference = IntensityDataIOFactory::readIntensityData(filename);
}


ObsoleteFunctionalTest::~ObsoleteFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}


void ObsoleteFunctionalTest::runTest()
{
    m_simulation->runSimulation();
    if(m_info.m_normalize) m_simulation->normalize();
}


int ObsoleteFunctionalTest::analyseResults()
{
    assert(m_simulation);
    assert(m_reference);
    boost::scoped_ptr<OutputData<double> > P_data(m_simulation->getIntensityData());

    double diff = IntensityDataFunctions::getRelativeDifference(*P_data,*m_reference);

    std::cout << getName() << " " << getDescription() << " " << diff
              << " " << (diff>m_info.m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > m_info.m_threshold ) return FAILED;
    return SUCCESS;
}
