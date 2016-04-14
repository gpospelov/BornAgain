#include "SimulationRegistry.h"
#include "IFunctionalTest.h"
#include "IntensityDataFunctions.h"
#include "SampleBuilderFactory.h"
#include <iostream>
#include <memory>

int TestBatchSimulation()
{
    SimulationRegistry sim_registry;
    const std::unique_ptr<GISASSimulation > simulation(sim_registry.createSimulation("MiniGISAS"));

    SampleBuilderFactory sampleFactory;
    SampleBuilder_t builder = sampleFactory.createBuilder("CylindersInBABuilder");

    simulation->setSampleBuilder(builder);
    simulation->runSimulation();
    const std::unique_ptr<OutputData<double > > reference(simulation->getDetectorIntensity());
    const std::unique_ptr<OutputData<double > > result(reference->clone());
    result->setAllTo(0.0);

    const int n_batches = 9;
    const double threshold = 2e-10;
    for(size_t i_batch=0; i_batch<n_batches; ++i_batch) {
        const std::unique_ptr<GISASSimulation > batch(simulation->clone());
        ThreadInfo threadInfo;
        threadInfo.n_threads = 1;
        threadInfo.n_batches = n_batches;
        threadInfo.current_batch = i_batch;
        batch->getOptions().setThreadInfo(threadInfo);

        batch->runSimulation();
        *result += *batch->getOutputData();
    }


    double diff = IntensityDataFunctions::getRelativeDifference(*result,*reference);

    std::cout << "BatchSimulation" << " " << "Running simulations in batch mode" << " " << diff
              << " " << (diff>threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > threshold ) return IFunctionalTest::FAILED;

    return IFunctionalTest::SUCCESS;
}


int main(int, char **)
{
    return TestBatchSimulation();
}


