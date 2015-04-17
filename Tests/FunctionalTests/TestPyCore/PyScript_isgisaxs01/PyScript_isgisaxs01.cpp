#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_CylinderAndPrisms");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for isgisaxs01"
              << "(Mixture of cylinders and prisms without interference):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}

