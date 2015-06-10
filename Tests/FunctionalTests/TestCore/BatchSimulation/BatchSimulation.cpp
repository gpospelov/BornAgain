#include "FunctionalTestRegistry.h"
#include "FileSystem.h"
#include "SimulationRegistry.h"
#include "IntensityDataIOFactory.h"
#include "MessageService.h"
#include "IntensityDataFunctions.h"
#include "IFunctionalTest.h"
#include <iostream>


int TestBatchSimulation()
{
    SimulationRegistry sim_registry;
    GISASSimulation *simulation = sim_registry.createSimulation("isgisaxs01");

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + "isgisaxs01_reference.int.gz";
    OutputData<double> *reference = IntensityDataIOFactory::readIntensityData(filename);


    OutputData<double> *result = reference->clone();
    result->setAllTo(0.0);

    const int n_batches = 9;
    const double threshold = 2e-10;
    for(size_t i_batch=0; i_batch<n_batches; ++i_batch) {
        GISASSimulation *batch = simulation->clone();
        ThreadInfo threadInfo;
        threadInfo.n_threads = 1;
        threadInfo.n_batches = n_batches;
        threadInfo.current_batch = i_batch;
        batch->setThreadInfo(threadInfo);

        batch->runSimulation();
        *result += *batch->getOutputData();

        delete batch;
    }


    double diff = IntensityDataFunctions::getRelativeDifference(*result,*reference);

    std::cout << "BatchSimulation" << " " << "Running simulations in batch mode" << " " << diff
              << " " << (diff>threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > threshold ) return FunctionalTest::FAILED;

    delete simulation;
    delete reference;

    return FunctionalTest::SUCCESS;
}


int main(int argc, char **argv)
{
    if(argc == 2) Utils::FileSystem::SetReferenceDataDir(argv[1]);
    //MSG::SetLevel(MSG::DEBUG);
    return TestBatchSimulation();
}


