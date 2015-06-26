// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SimulationRegistry.cpp
//! @brief     Implement class SimulationRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
        "isgisaxs04_1DDL", StandardSimulations::IsGISAXS041DDL,
        "Interference function of radial paracrystal");

    registerItem(
        "isgisaxs04_2DDL", StandardSimulations::IsGISAXS042DDL,
        "Interference function of 2D paracrystal");






    registerItem(
        "isgisaxs02", StandardSimulations::IsGISAXS02,
        "Mixture cylinder particles with different size distribution");

    registerItem(
        "cylinders_ba", StandardSimulations::CylindersInBA,
        "Cylinder formfactor in BA");
    registerItem(
        "cylinders_dwba", StandardSimulations::CylindersInDWBA,
        "Cylinder formfactor in DWBA");
    registerItem(
        "cylinders_basize", StandardSimulations::CylindersWithSizeDistribution,
        "Cylinder formfactor in BA with size distribution");

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




    registerItem(
        "gui_multiple_layouts", StandardSimulations::gui_MultipleLayouts,
        "GUI: Mixture of Cylinders and Prisms using Multiple Layouts");


    // ---------------------------------------------------------------------------------------------
    // toward functional tests refactoring
    // ---------------------------------------------------------------------------------------------

    registerItem("BasicGISAS", StandardSimulations::BasicGISAS,
                 "Basic GISAS simulation with the detector phi[0,2], theta[0,2]");

    registerItem("MiniGISAS", StandardSimulations::MiniGISAS,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2]");

    registerItem("MiniGISASBeamDivergence", StandardSimulations::MiniGISASBeamDivergence,
                 "GISAS simulation with small detector and beam divergence");

    registerItem("MiniGISASDetectorResolution", StandardSimulations::MiniGISASDetectorResolution,
                 "GISAS simulation with small detector and detector resolution");

    registerItem("IsGISAXSSimulation1", StandardSimulations::IsGISAXSSimulation1,
                 "Typical IsGISAXS simulation with the detector theta[-1,1], phi[0,2]");
}


GISASSimulation *SimulationRegistry::createSimulation(const std::string& name)
{
    GISASSimulation *result = createItem(name);
    return result;
}


