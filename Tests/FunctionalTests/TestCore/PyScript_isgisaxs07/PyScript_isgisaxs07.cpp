#include "PyScriptTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_isgisaxs07");
    bool test = PyScriptTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs07"
              << "(Mixture of different particles a la IsGISAXS morphology file):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}

