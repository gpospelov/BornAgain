#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_Interference2DSquareLattice");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs06a"
              << "(2D lattice with disorders):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}
