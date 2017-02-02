// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      unused/OMPISimulation.cpp
//! @brief     Implements class OMPISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OMPISimulation.h"

#ifdef BORNAGAIN_OPENMPI

void OMPISimulation::runSimulation(Simulation * simulation)
{
    MPI_Status st;

    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_size == 1) {
        simulation->runSimulation();
        return;
    }

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if(world_rank != 0) {
        ThreadInfo threadInfo = simulation->m_thread_info;
        threadInfo.n_batches = world_size - 1;
        threadInfo.current_batch = world_rank - 1;
        simulation->setThreadInfo(threadInfo);
        simulation->runSimulation();

        std::vector<double> raw = simulation->getOutputData()->getRawDataVector();
        MPI_Send(&raw[0], raw.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

    }
    if(world_rank==0) {
        size_t total_size = simulation->getOutputData()->getAllocatedSize();
        std::vector<double> sum_of_raw;
        sum_of_raw.resize(total_size, 0.0);
        for(int i=1; i<world_size; ++i) {
            std::vector<double> raw;
            raw.resize(total_size, 0.0);
            MPI_Recv(&raw[0], total_size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
            for(size_t i_raw=0; i_raw<total_size; ++i_raw)
                sum_of_raw[i_raw] += raw[i_raw];
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
    throw Exceptions::RuntimeErrorException(
        "OMPISimulation::runSimulation() -> Error! Can't run OpenMPI simulation. "
        "The package was compiled without OpenMPI support (compile with -DBORNAGAIN_OPENMPI=ON)" );
}

#endif
