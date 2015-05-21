#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    GISASSimulation *simulation =
            simulationRegistry.createSimulation("gui_Interference1DParaCrystal");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs04_1DDL"
              << "(Radial paracrystal):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}


