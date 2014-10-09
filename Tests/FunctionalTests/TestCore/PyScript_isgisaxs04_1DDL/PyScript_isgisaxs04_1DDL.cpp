#include "PyScriptTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_isgisaxs04_1DDL");
    bool test = PyScriptTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs04_1DDL"
              << "(1D paracrystal):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}


