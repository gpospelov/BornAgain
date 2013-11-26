#include "SimulationRegistry.h"
#include "StandardSimulations.h"




SimulationRegistry::SimulationRegistry()
{

    registerItem(
        "mesocrystal01", StandardSimulations::MesoCrystal01,
        "mesocrystals of cylindrical shape composed by spherical nanoparticles");

	registerItem(
        "PolarizedDWBAZeroMag", StandardSimulations::PolarizedDWBAZeroMag,
        "polarized DWBA with zero magnetic field");

}


Simulation *SimulationRegistry::createSimulation(const std::string& name)
{
    Simulation *result = createItem(name);
    return result;
}


