// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SimulationFactory.cpp
//! @brief     Implement class SimulationFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/SimulationFactory.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/StandardSamples/StandardSimulations.h"

SimulationFactory::SimulationFactory()
{
    registerItem("BasicGISAS", StandardSimulations::BasicGISAS,
                 "Basic GISAS simulation with the detector phi[0,2], theta[0,2]");

    registerItem("BasicGISAS00", StandardSimulations::BasicGISAS00,
                 "Basic GISAS for polarization studies");

    registerItem("BasicPolarizedGISAS", StandardSimulations::BasicPolarizedGISAS,
                 "Basic GISAS for spin flip channel");

    registerItem("MiniGISAS", StandardSimulations::MiniGISAS,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2]");

    registerItem("MiniGISAS_v2", StandardSimulations::MiniGISAS_v2,
                 "GISAS simulation with small 25x25 detector and phi[-1,1], theta[0,]");

    registerItem("MiniGISASBeamDivergence", StandardSimulations::MiniGISASBeamDivergence,
                 "GISAS simulation with small detector and beam divergence");

    registerItem("MiniGISASDetectorResolution", StandardSimulations::MiniGISASDetectorResolution,
                 "GISAS simulation with small detector and detector resolution");

    registerItem("MiniGISASSpecular", StandardSimulations::MiniGISASSpecularPeak,
                 "GISAS simulation including specular peak");

    registerItem("GISASWithMasks", StandardSimulations::GISASWithMasks,
                 "GISAS simulation with small detector and various masks");

    registerItem("MaxiGISAS", StandardSimulations::MaxiGISAS,
                 "GISAS simulation with large detector to test performance");

    registerItem("MaxiGISAS00", StandardSimulations::MaxiGISAS00,
                 "GISAS simulation with large detector to test performance");

    registerItem("IsGISAXSSimulation1", StandardSimulations::IsGISAXSSimulation1,
                 "Typical IsGISAXS simulation with the detector theta[-1,1], phi[0,2]");

    registerItem("IsGISAXSSimulation2", StandardSimulations::IsGISAXSSimulation2,
                 "Typical IsGISAXS simulation with the detector theta[0,1], phi[0,2]");

    // polarization

    registerItem("MiniGISASPolarizationPP", StandardSimulations::MiniGISASPolarizationPP,
                 "GISAS simulation measuring plus-plus polarization");

    registerItem("MiniGISASPolarizationPM", StandardSimulations::MiniGISASPolarizationPM,
                 "GISAS simulation measuring spin flip (+-) channel");

    registerItem("MiniGISASPolarizationMP", StandardSimulations::MiniGISASPolarizationMP,
                 "GISAS simulation measuring spin flip (-+) channel");

    registerItem("MiniGISASPolarizationMM", StandardSimulations::MiniGISASPolarizationMM,
                 "GISAS simulation measuring minus-minus polarization");

    // rectangular detectors

    registerItem("RectDetectorGeneric", StandardSimulations::RectDetectorGeneric,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToSample", StandardSimulations::RectDetectorPerpToSample,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToDirectBeam", StandardSimulations::RectDetectorPerpToDirectBeam,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToReflectedBeam",
                 StandardSimulations::RectDetectorPerpToReflectedBeam,
                 "Rectangular detector with generic alignment");

    registerItem("RectDetectorPerpToReflectedBeamDpos",
                 StandardSimulations::RectDetectorPerpToReflectedBeamDpos,
                 "Rectangular detector with generic alignment");

    registerItem("ExtraLongWavelengthGISAS", StandardSimulations::ExtraLongWavelengthGISAS,
                 "GISAS with rectangular detector and extra long wavelentgh");

    // Monte-Carlo
    registerItem("MiniGISASMonteCarlo", StandardSimulations::MiniGISASMonteCarlo,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2], "
                 "in Monte-Carlo mode");

    // region of interest

    registerItem("SphericalDetWithRoi", StandardSimulations::SphericalDetWithRoi,
                 "Spherical detector with ROI and mask");
    registerItem("RectDetWithRoi", StandardSimulations::RectDetWithRoi,
                 "Rectangular detector with ROI and mask");

    // background

    registerItem("ConstantBackground", StandardSimulations::ConstantBackgroundGISAS,
                 "Simulation with a constant background value");

    // specular simulations

    registerItem("BasicSpecular", StandardSimulations::BasicSpecular,
                 "Basic specular simulation with [0, 5] deg incident angle range and "
                 "1.54 angstroms wavelength.");

    registerItem("BasicSpecularQ", StandardSimulations::BasicSpecularQ,
                 "Same as BasicSpecular, but the qz range is passed to the simulation directly");

    registerItem("SpecularWithGaussianBeam", StandardSimulations::SpecularWithGaussianBeam,
                 "The same as BasicSpecular, but implies beam size finiteness (beam is of the same "
                 "size as the sample). The beam is gaussian in shape.");

    registerItem("SpecularWithSquareBeam", StandardSimulations::SpecularWithSquareBeam,
                 "The same as BasicSpecular, but implies beam size finiteness (beam is of the same "
                 "size as the sample). The beam is square in shape.");

    registerItem("SpecularDivergentBeam", StandardSimulations::SpecularDivergentBeam,
                 "Simulation implies beam divergence both in wavelength and "
                 "inclination angle.");

    registerItem("TOFRWithRelativeResolution", StandardSimulations::TOFRWithRelativeResolution,
                 "Q-defined reflectometric scan with relative resolution");

    registerItem("TOFRWithPointwiseResolution", StandardSimulations::TOFRWithPointwiseResolution,
                 "Q-defined reflectometric scan with pointwise resolution.");

    registerItem("OffSpecMini", StandardSimulations::MiniOffSpec,
                 "Mini OffSpecular simulation for resonator experiment.");

    // polarized specular

    registerItem("BasicSpecularPP", StandardSimulations::BasicSpecularPP,
                 "Basic specular simulation for magnetized samples, ++ channel");

    registerItem("BasicSpecularMM", StandardSimulations::BasicSpecularMM,
                 "Basic specular simulation for magnetized samples, -- channel");

    registerItem("BasicQSpecularPP", StandardSimulations::BasicSpecularQPP,
                 "Basic q-defined specular simulation for magnetized samples, ++ channel");

    registerItem("BasicQSpecularMM", StandardSimulations::BasicSpecularQMM,
                 "Basic q-defined specular simulation for magnetized samples, -- channel");

    // depth probe simulations

    registerItem("BasicDepthProbe", StandardSimulations::BasicDepthProbe,
                 "Basic 20x20 depth probe simulation with [0, 1] deg angle and [-100, 100] z span");

    registerItem("MiniGISASFit", StandardSimulations::MiniGISASFit,
                 "GISAS simulation with small 25x25 detector and phi[-2,2], theta[0,2]. "
                 "Beam intensity is set");
}
