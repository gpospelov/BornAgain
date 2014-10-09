#include "PyScriptTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_isgisaxs11");
    bool test = PyScriptTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs11"
              << "(Core shell nanoparticles):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}



