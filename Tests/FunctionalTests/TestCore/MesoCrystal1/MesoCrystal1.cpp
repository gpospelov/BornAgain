#include "MesoCrystal1.h"
#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"
#include "Units.h"
#include "Types.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"

using namespace FunctionalTests;



MesoCrystal1::MesoCrystal1()
: m_name("MesoCrystal1")
, m_description("Meso crystal simulation")
, m_result(0)
, m_reference(0)
{ }


void MesoCrystal1::MesoCrystal1::run(const std::string &path_to_data)
{
    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("mesocrystal01");
    simulation->getSampleBuilder()->setParameterValue("nphi_rotations", 2.);

    // loading reference data
    std::string filename = path_to_data + "mesocrystal1_reference_v2_nphi2.txt.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    // setting detector axis as in reference data
    simulation->setDetectorParameters(*m_reference);

    simulation->runSimulation();
    simulation->normalize();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int MesoCrystal1::analyseResults()
{
    const double threshold(1e-10);

    // calculating average relative difference
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

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
    FunctionalTests::MesoCrystal1 test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif

