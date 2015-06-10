#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    GISASSimulation *simulation =
            simulationRegistry.createSimulation("gui_multiple_layouts");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for multiple_layout_builder"
              << "(Multiple Particle Layouts used):"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}



