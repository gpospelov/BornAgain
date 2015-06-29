#include "SimulationRegistry.h"
#include "IntensityDataFunctions.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include "Distributions.h"
#include "Units.h"

int main(int argc, char **argv)
{
    SimulationRegistry sim_registry;
    GISASSimulation* simulation = sim_registry.createSimulation("isgisaxs06d");

    // loading reference data
    std::string filename = Utils::FileSystem::GetReferenceDataDir() +
            "isgisaxs06_reference_variants.int.gz";
    OutputData<double> *reference =
            IntensityDataIOFactory::readIntensityData(filename);

    // running simulation and copying data
    int nbins = 3;
    DistributionGate gate(0.0*Units::degree, 240.0*Units::degree);
    simulation->addParameterDistribution("*/xi", gate, nbins);
    simulation->runSimulation();
    OutputData<double> *result = simulation->getIntensityData();

    const double threshold(2e-10);
    // Calculating average relative difference.
    double diff = IntensityDataFunctions::getRelativeDifference(
                *result,*reference);

    delete simulation;
    delete result;
    delete reference;

    // Assess result.
    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << "isgisaxs06_lattice4" << " " << "2D lattice variants" << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}

