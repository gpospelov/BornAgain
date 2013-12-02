#include "SimulationRegistry.h"
#include "StandardSimulations.h"




SimulationRegistry::SimulationRegistry()
{
    registerItem(
                "isgisaxs01", StandardSimulations::IsGISAXS01,
        "Mixture of cylinders and prisms without interference");

    registerItem(
                "isgisaxs02", StandardSimulations::IsGISAXS02,
        "Mixture cylinder particles with different size distribution");

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


