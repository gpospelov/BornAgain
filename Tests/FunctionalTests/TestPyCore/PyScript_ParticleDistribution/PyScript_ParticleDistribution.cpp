#include "PyGenTools.h"
#include "SimulationRegistry.h"

int main()
{
    SimulationRegistry simulationRegistry;
    GISASSimulation *simulation =
            simulationRegistry.createSimulation("part_distribution");
    bool test = PyGenTools::testPyScript(simulation);
    std::cout << "Python Script Generation Test for ParticleDistribution"
              << (test? "[OK]" : "[FAILED]") << std::endl;
    return (test ? 0 : 1);
}

