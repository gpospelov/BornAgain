#include "MesoCrystal1.h"
#include "SampleBuilder.h"

#include "Simulation.h"
#include "ResolutionFunction2DSimple.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"
#include "Units.h"
#include "Types.h"

using namespace FunctionalTests;



MesoCrystal1::MesoCrystal1()
    : m_name("MesoCrystal1")
    , m_description("Meso crystal simulation")
{ }


void MesoCrystal1::MesoCrystal1::run(const std::string &path_to_data)
{
    // setting up sample and simulation
    SampleBuilder *sample_builder = new SampleBuilder();
    Simulation *simulation = createSimulation();
    simulation->setSampleBuilder( sample_builder );

    // loading reference data
    std::string filename = path_to_data + "mesocrystal1b_reference.txt.gz";
    m_reference = OutputDataIOFactory::getOutputData(filename);

    // setting detector axis as in reference data
    simulation->setDetectorParameters(*m_reference);

    //running simulation
    simulation->runSimulation();
    simulation->normalize();
    m_result = simulation->getOutputDataClone();
//    OutputDataIOFactory::writeOutputData(*result, "reference.txt");
}


// create simulation
Simulation *MesoCrystal1::createSimulation()
{
    Simulation *simulation = new Simulation();
    simulation->setBeamParameters(1.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);
    simulation->setBeamIntensity(5.0090e+12);
    simulation->setDetectorResolutionFunction(new ResolutionFunction2DSimple(0.0002, 0.0002));
    return simulation;
}


int MesoCrystal1::analyseResults()
{
    const double threshold(1e-10);

    // calculating average relative difference
    *m_result -= *m_reference;
    *m_result /= *m_reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold || std::isnan(diff)) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}



#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToExecutable(argv[0]) + "../../../ReferenceData/BornAgain/";
}

int main(int argc, char **argv)
{
    FunctionalTests::MesoCrystal1 test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif

