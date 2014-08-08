// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SimulationRegistry.cpp
//! @brief     Implement class SimulationRegistry.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
        "isgisaxs06a", StandardSimulations::IsGISAXS06L1,
        "2D lattice with disorders");
    registerItem(
        "isgisaxs06b", StandardSimulations::IsGISAXS06L2,
        "2D lattice centered");
    registerItem(
        "isgisaxs06c", StandardSimulations::IsGISAXS06L3,
        "2D lattice rotated");
    registerItem(
        "isgisaxs06d", StandardSimulations::IsGISAXS06L4,
        "2D lattice variants");

    registerItem(
        "isgisaxs07", StandardSimulations::IsGISAXS07,
        "Mixture of different particles a la IsGISAXS morphology file");

    registerItem(
        "isgisaxs08a", StandardSimulations::IsGISAXS08a,
        "2DDL paracrystal lattice");
    registerItem(
        "isgisaxs08b", StandardSimulations::IsGISAXS08b,
        "2DDL paracrystal lattice with isotropic pdfs");

    registerItem(
        "isgisaxs09a", StandardSimulations::IsGISAXS09a,
        "Pyramids on top of substrate");
    registerItem(
        "isgisaxs09b", StandardSimulations::IsGISAXS09b,
        "Rotated pyramids on top of substrate");

    registerItem(
        "isgisaxs10", StandardSimulations::IsGISAXS10,
        "Cylinders with interference on top of substrate");

    registerItem(
        "isgisaxs11", StandardSimulations::IsGISAXS11,
        "Core shell nanoparticles");

    registerItem(
        "isgisaxs15", StandardSimulations::IsGISAXS15,
        "Size spacing correlation approximation");

    registerItem(
        "mesocrystal01", StandardSimulations::MesoCrystal01,
        "Mesocrystals of cylindrical shape composed by spherical nanoparticles");

    registerItem(
        "polmagcylinders1", StandardSimulations::PolarizedDWBAMagCylinders1,
        "Polarized DWBA with zero magnetic field");
    registerItem(
        "polmagcylinders2", StandardSimulations::PolarizedDWBAMagCylinders2,
        "Polarized DWBA with non-zero magnetic field");

    registerItem(
        "LayerWithRoughness", StandardSimulations::LayerWithRoughness,
        "Layers with correlated roughness");

    registerItem(
        "ripple2", StandardSimulations::Ripple2,
        "Triangular ripple within the 1D-paracrystal model");

    registerItem(
        "ripple1", StandardSimulations::Ripple1,
        "Cosine ripple within the 1D-paracrystal model");

}


Simulation *SimulationRegistry::createSimulation(const std::string& name)
{
    Simulation *result = createItem(name);
    return result;
}


