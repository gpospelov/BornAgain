#include "OMPISimulation.h"
#include "Simulation.h"
#include "OutputData.h"
#include "Exceptions.h"
#include "MessageService.h"
#include "OutputDataFunctions.h"

#ifdef BORNAGAIN_OPENMPI

#include <mpi.h>


void OMPISimulation::runSimulation(Simulation * simulation)
{
    MPI_Status st;

    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_size == 1) {
        std::cout << "OMPISimulation::runSimulation() -> Warning. Not an OpenMPI environment." << std::endl;
        std::cout << "For now continuing without OpenMPI support" << std::endl;
        simulation->runSimulation();
        return;
    }

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);


    msglog(MSG::INFO) << "OMPISimulation::runSimulation() -> "
                      << " from processor " << processor_name
                      << " , rank " << world_rank
                      << " out of " << world_size << " processors.";


    if(world_rank != 0) {
        ThreadInfo threadInfo;
        threadInfo.n_batches = world_size - 1;
        threadInfo.current_batch = world_rank - 1;
        std::cout << " xxx preparing to run " << threadInfo.n_batches << " " << threadInfo.current_batch << std::endl;
        simulation->setThreadInfo(threadInfo);
        simulation->runSimulation();

        std::vector<double> raw = simulation->getOutputData()->getRawDataVector();
        std::cout << " xxx " << threadInfo.n_batches << " " << threadInfo.current_batch << " ... sending raw of size" << raw.size() << std::endl;
        MPI_Send(&raw[0], raw.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

    }
    if(world_rank==0) {
        size_t total_size = simulation->getOutputData()->getAllocatedSize();
        std::vector<double> sum_of_raw;
        sum_of_raw.resize(total_size, 0.0);
        std::cout << " preparing to receive" << std::endl;
        for(int i=1; i<world_size; ++i) {
            std::vector<double> raw;
            raw.resize(total_size, 0.0);
            std::cout << " ... receiving " << i << std::endl;
            MPI_Recv(&raw[0], total_size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
            for(size_t i_raw=0; i_raw<total_size; ++i_raw) {
                sum_of_raw[i_raw] += raw[i_raw];
            }
        }

        simulation->m_intensity_map.setRawDataVector(sum_of_raw);

    }


}


#else
// -----------------------------------------------------------------------------
// No OpenMPI support
// -----------------------------------------------------------------------------

void OMPISimulation::runSimulation(Simulation * /* simulation */)
{
    throw RuntimeErrorException("OMPISimulation::runSimulation() -> Error! Can't run OpenMPI simulation. The package was compiled without OpenMPI support (compile with -DBORNAGAIN_OPENMPI=ON");
}

#endif
