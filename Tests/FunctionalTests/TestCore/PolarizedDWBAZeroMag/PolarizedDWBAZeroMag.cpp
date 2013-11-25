#include "PolarizedDWBAZeroMag.h"
#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"
#include "Units.h"
#include "Types.h"
#include "SimulationRegistry.h"

using namespace FunctionalTests;



PolarizedDWBAZeroMag::PolarizedDWBAZeroMag()
: m_name("PolarizedDWBAZeroMag")
, m_description("PolarizedDWBAZeroMag simulation")
, m_result(0)
, m_reference(0)
{ }


void PolarizedDWBAZeroMag::PolarizedDWBAZeroMag::run(const std::string &path_to_data)
{
    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("PolarizedDWBAZeroMag");
    //simulation->getSampleBuilder()->setMatchedParametersValue("*/nphi_rotations", 2.);

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


int PolarizedDWBAZeroMag::analyseResults()
{
    const double threshold(1e-10);

    // calculating average relative difference
    *m_result -= *m_reference;
    *m_result /= *m_reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin();
            it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

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
    FunctionalTests::PolarizedDWBAZeroMag test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif

