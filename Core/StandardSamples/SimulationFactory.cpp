// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SimulationFactory.cpp
//! @brief     Implement class SimulationFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationFactory.h"
#include "GISASSimulation.h"
#include "RealParameter.h"
#include "StandardSimulations.h"

SimulationFactory::SimulationFactory()
{
    registerItem("BasicGISAS",
                 StandardSimulation::BasicGISAS,
                 "Basic GISAS simulation with the detector phi[0,2], theta[0,2]");

    registerItem("BasicGISAS00",
                 StandardSimulation::BasicGISAS00,
                 "Basic GISAS for polarization studies");

    registerItem("MiniGISAS",
                 StandardSimulation::MiniGISAS,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2]");

    registerItem("MiniGISAS_v2",
                 StandardSimulation::MiniGISAS_v2,
                 "GISAS simulation with small 25x25 detector and phi[-1,1], theta[0,]");

    registerItem("MiniGISASBeamDivergence",
                 StandardSimulation::MiniGISASBeamDivergence,
                 "GISAS simulation with small detector and beam divergence");

    registerItem("MiniGISASDetectorResolution",
                 StandardSimulation::MiniGISASDetectorResolution,
                 "GISAS simulation with small detector and detector resolution");

    registerItem("GISASWithMasks",
                 StandardSimulation::GISASWithMasks,
                 "GISAS simulation with small detector and various masks");

    registerItem("MaxiGISAS",
                 StandardSimulation::MaxiGISAS,
                 "GISAS simulation with large detector to test performance");

    registerItem("MaxiGISAS00",
                 StandardSimulation::MaxiGISAS00,
                 "GISAS simulation with large detector to test performance");

    registerItem("IsGISAXSSimulation1",
                 StandardSimulation::IsGISAXSSimulation1,
                 "Typical IsGISAXS simulation with the detector theta[-1,1], phi[0,2]");

    registerItem("IsGISAXSSimulation2",
                 StandardSimulation::IsGISAXSSimulation2,
                 "Typical IsGISAXS simulation with the detector theta[0,1], phi[0,2]");

    // polarization

    registerItem(
        "polmagcylinders2", StandardSimulation::PolarizedDWBAMagCylinders2,
        "Polarized DWBA with non-zero magnetic field");

    // rectangular detectors

    registerItem("RectDetectorGeneric",
                 StandardSimulation::RectDetectorGeneric,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToSample",
                 StandardSimulation::RectDetectorPerpToSample,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToDirectBeam",
                 StandardSimulation::RectDetectorPerpToDirectBeam,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToReflectedBeam",
                 StandardSimulation::RectDetectorPerpToReflectedBeam,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToReflectedBeamDpos",
                 StandardSimulation::RectDetectorPerpToReflectedBeamDpos,
                 "Rectangular detector with generic alignment");

    // Monte-Carlo
    registerItem("MiniGISASMonteCarlo",
                 StandardSimulation::MiniGISASMonteCarlo,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2], "
                 "in Monte-Carlo mode");

    // region of interest

    registerItem("SphericalDetWithRoi",
                 StandardSimulation::SphericalDetWithRoi,
                 "Spherical detector with ROI and mask");
    registerItem("RectDetWithRoi",
                 StandardSimulation::RectDetWithRoi,
                 "Rectangular detector with ROI and mask");
}
