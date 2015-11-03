#include "SimulationRegistry.h"
#include "IntensityDataFunctions.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include "Distributions.h"
#include "SampleBuilderFactory.h"
#include "Units.h"

int main()
{
    SimulationRegistry sim_registry;
    GISASSimulation* simulation = sim_registry.createSimulation("IsGISAXSSimulation2");

    SampleBuilderFactory factory;
    SampleBuilder_t builder = factory.createBuilder("CustomRotatedLatticeBuilder");
    simulation->setSampleBuilder(builder);


    // loading reference data
    std::string filename = Utils::FileSystem::GetReferenceDataDir() +
            "isgisaxs06_reference_variants.int.gz";
    OutputData<double> *reference =
            IntensityDataIOFactory::readOutputData(filename);

    // running simulation and copying data
    int nbins = 3;
    DistributionGate gate(0.0*Units::degree, 240.0*Units::degree);
    simulation->addParameterDistribution("*/xi", gate, nbins);
    simulation->runSimulation();
    OutputData<double> *result = simulation->getDetectorIntensity();

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

