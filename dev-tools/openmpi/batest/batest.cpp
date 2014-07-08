#include <iostream>
#include "SimulationRegistry.h"

int main()
{

    std::cout << "Hello World" << std::endl;
    
    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs01");

    simulation->runOMPISimulation();
    
    return 0;
}