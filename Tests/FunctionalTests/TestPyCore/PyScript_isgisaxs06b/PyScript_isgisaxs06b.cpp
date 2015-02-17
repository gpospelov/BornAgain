#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_isgisaxs06b");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs06b"
              << "(2D lattice centered):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}
