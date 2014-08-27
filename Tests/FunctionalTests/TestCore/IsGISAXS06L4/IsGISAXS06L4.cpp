#include "SimulationRegistry.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "IntensityDataFunctions.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"

int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);

    SimulationRegistry sim_registry;
    Simulation* simulation = sim_registry.createSimulation("isgisaxs06d");

    // loading reference data
    std::string filename = Utils::FileSystem::GetReferenceDataDir() + "isgisaxs06_reference_variants.int.gz";
    OutputData<double> *reference = IntensityDataIOFactory::readIntensityData(filename);

    // running simulation and copying data
    OutputData<double> *result = simulation->getIntensityData();
    result->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticDoubleGate xg(xi_min, xi_max);
    StochasticSampledParameter xi(xg, nbins, xi_min, xi_max);
    for (size_t i=0; i<xi.getNbins(); ++i) {
        double xi_value = xi.getBinValue(i);
        double probability = xi.getNormalizedProbability(i);
        simulation->getSampleBuilder()->setParameterValue("xi",xi_value);
        simulation->runSimulation();
        OutputData<double> *p_single_output = simulation->getIntensityData();
        p_single_output->scaleAll(probability);
        *result += *p_single_output;
        delete p_single_output;
    }

    const double threshold(2e-10);
    // Calculating average relative difference.
    double diff = IntensityDataFunctions::getRelativeDifference(*result,*reference);

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

