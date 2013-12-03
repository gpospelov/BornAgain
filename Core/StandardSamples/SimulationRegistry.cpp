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
        "isgisaxs06_lattice1", StandardSimulations::IsGISAXS06L1,
        "IsGISAXS06 example, 2D lattice with different disorders");
    registerItem(
        "isgisaxs06_lattice2", StandardSimulations::IsGISAXS06L2,
        "IsGISAXS06 example, 2D lattice centered");
    registerItem(
        "isgisaxs06_lattice3", StandardSimulations::IsGISAXS06L3,
        "IsGISAXS06 example, 2D lattice rotated");
    registerItem(
        "isgisaxs06_lattice4", StandardSimulations::IsGISAXS06L4,
        "IsGISAXS06 example, 2D lattice variants");

    registerItem(
        "isgisaxs07", StandardSimulations::IsGISAXS07,
        "Mixture of different particles defined in morphology file");


    registerItem(
        "isgisaxs08_2DDL", StandardSimulations::IsGISAXS082DDL,
        "IsGISAXS08 example, 2DDL lattice");

    registerItem(
        "isgisaxs08_2DDL2", StandardSimulations::IsGISAXS082DDL2,
        "IsGISAXS08 example, 2DDL lattice with isotropic pdfs");

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


