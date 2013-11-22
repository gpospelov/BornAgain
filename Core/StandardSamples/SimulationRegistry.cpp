#include "SimulationRegistry.h"
#include "StandardSimulations.h"




SimulationRegistry::SimulationRegistry()
{

    registerItem(
        "mesocrystal01", StandardSimulations::MesoCrystal01,
        "mesocrystals of cylindrical shape composed by spherical nanoparticles");

}


Simulation *SimulationRegistry::createSimulation(const std::string& name)
{
    Simulation *result = createItem(name);
    return result;
}


