#include <iostream>
#include "SimulationRegistry.h"
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);


    std::cout << "Hello World" << std::endl;
    
    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs01");

    simulation->runOMPISimulation();

    MPI_Finalize();
    
    return 0;
}