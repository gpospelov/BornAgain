#include "OMPISimulation.h"
#include "Simulation.h"
#include "OutputData.h"
#include "Exceptions.h"

#ifdef BORNAGAIN_OPENMPI

#include <mpi.h>


void OMPISimulation::runSimulation(const Simulation * /* simulation */)
{

    MPI_Status st;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);

    if(world_rank != 0) {
        std::cout << "XXX not a 0" << std::endl;
        Simulation *sim = simulation->clone();
        ThreadInfo threadInfo;
        threadInfo.n_batches = world_size - 1;
        threadInfo.current_batch = world_rank - 1;
        std::cout << " xxx preparing to run " << threadInfo.n_batches << " " << threadInfo.current_batch << std::endl;
        sim->setThreadInfo(threadInfo);
        sim->runSimulation();

        //std::vector<double> raw = sim->getOutputData()->getRawDataVector();
        std::vector<double> raw;
        raw.resize(1000000);
        std::cout << " xxx " << threadInfo.n_batches << " " << threadInfo.current_batch << " ... sending" << std::endl;
        MPI_Send(&raw[0], raw.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

    }
    if(world_rank==0) {
        std::cout << " preparing to receive" << std::endl;
//        std::vector<double> raw = simulation->getOutputData()->getRawDataVector();
        std::vector<double> raw;
        raw.resize(1000000);
        for(int i=1; i<world_size; ++i) {
            std::cout << " ... receiving " << i << std::endl;
            MPI_Recv(&raw[0], raw.size(), MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
        }

    }


}


#else
// -----------------------------------------------------------------------------
// No OpenMPI support
// -----------------------------------------------------------------------------

void OMPISimulation::runSimulation(const Simulation * /* simulation */)
{
    throw RuntimeErrorException("OMPISimulation::runSimulation() -> Error! Can't run OpenMPI simulation. The package was compiled without OpenMPI support (compile with -DBORNAGAIN_OPENMPI=ON");
}

#endif
