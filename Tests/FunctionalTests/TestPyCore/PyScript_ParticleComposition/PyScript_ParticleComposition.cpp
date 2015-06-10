#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    Simulation *simulation =
            simulationRegistry.createSimulation("gui_ParticleComposition");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for ParticleDistribution"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}

