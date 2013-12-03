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
        "isgisaxs03_ba", StandardSimulations::IsGISAXS03BA,
        "Cylinder formfactor in BA");

    registerItem(
        "isgisaxs03_dwba", StandardSimulations::IsGISAXS03DWBA,
        "Cylinder formfactor in DWBA");

    registerItem(
        "isgisaxs03_basize", StandardSimulations::IsGISAXS03BAsize,
        "Cylinder formfactor in BA with size distribution");

    registerItem(
        "isgisaxs04_1DDL", StandardSimulations::IsGISAXS041DDL,
        "IsGISAXS04 example, 1DDL structure factor");

    registerItem(
        "isgisaxs04_2DDL", StandardSimulations::IsGISAXS042DDL,
        "IsGISAXS04 example, 2DDL structure factor");

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


