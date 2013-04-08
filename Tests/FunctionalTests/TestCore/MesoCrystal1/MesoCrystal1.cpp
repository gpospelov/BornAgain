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
    : m_test_name("MesoCrystal1")
    , m_test_description("Meso crystal simulation")
{ }


MesoCrystal1::~MesoCrystal1()
{ }


int MesoCrystal1::MesoCrystal1::run()
{
    // setting up sample and simulation
    SampleBuilder *sample_builder = new SampleBuilder();
    Simulation *simulation = createSimulation();
    simulation->setSampleBuilder( sample_builder );

    // loading reference data
    std::string filename = Utils::FileSystem::GetHomePath() +
        "/Tests/FunctionalTests/TestCore/MesoCrystal1/mesocrystal1_reference.txt.gz";
    OutputData<double > *reference_data = OutputDataIOFactory::getOutputData(filename);

    // setting detector axis as in reference data
    simulation->setDetectorParameters(*reference_data);

    //running simulation
    simulation->runSimulation();
    simulation->normalize();
    OutputData<double > *result = simulation->getOutputDataClone();

    // analysing results
    double diff = getDifference(result, reference_data);
    const double threshold(1e-10);
    bool status_ok(true);
    if( diff > threshold || std::isnan(diff) ) status_ok=false;

    delete sample_builder;
    delete simulation;
    delete result;
    delete reference_data;

    std::cout << m_test_name << " " << m_test_description << " " <<
        (status_ok ? "[OK]" : "[FAILED]") << std::endl;

    return (status_ok ? 0 : 1);
}


double MesoCrystal1::getDifference(OutputData<double> *result, const OutputData<double> *reference)
{
    double diff(0);
    // Calculating average relative difference.
    *result -= *reference;
    *result /= *reference;
    for(OutputData<double>::const_iterator it =
            result->begin(); it!=result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= result->getAllocatedSize();
    return diff;
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




#ifdef STANDALONE
int main()
{
    //Utils::EnableFloatingPointExceptions();
    FunctionalTests::MesoCrystal1 test;
    return test.run();
}
#endif

