// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/StandardSimulations.h
//! @brief     Defines namespace and functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef STANDARDSIMULATIONS_H
#define STANDARDSIMULATIONS_H

#include "WinDllMacros.h"

class DepthProbeSimulation;
class GISASSimulation;
class SpecularSimulation;
class OffSpecSimulation;

//! Standard pre-defined simulations.

namespace StandardSimulations {

// Special tests:
BA_CORE_API_ GISASSimulation* PolarizedDWBAMagCylinders2();

// CoreSuite tests:
BA_CORE_API_ GISASSimulation* BasicGISAS();
BA_CORE_API_ GISASSimulation* BasicGISAS00();
BA_CORE_API_ GISASSimulation* BasicPolarizedGISAS();
BA_CORE_API_ GISASSimulation* MiniGISAS();
BA_CORE_API_ GISASSimulation* MiniGISAS_v2();
BA_CORE_API_ GISASSimulation* MiniGISASBeamDivergence();
BA_CORE_API_ GISASSimulation* MiniGISASDetectorResolution();
BA_CORE_API_ GISASSimulation* MiniGISASPolarizationPP();
BA_CORE_API_ GISASSimulation* MiniGISASSpinFlipZ();
BA_CORE_API_ GISASSimulation* MiniGISASSpecularPeak();
BA_CORE_API_ GISASSimulation* GISASWithMasks();
BA_CORE_API_ GISASSimulation* MaxiGISAS();
BA_CORE_API_ GISASSimulation* MaxiGISAS00();
BA_CORE_API_ GISASSimulation* IsGISAXSSimulation1();
BA_CORE_API_ GISASSimulation* IsGISAXSSimulation2();
BA_CORE_API_ GISASSimulation* RectDetectorGeneric();
BA_CORE_API_ GISASSimulation* RectDetectorPerpToSample();
BA_CORE_API_ GISASSimulation* RectDetectorPerpToDirectBeam();
BA_CORE_API_ GISASSimulation* RectDetectorPerpToReflectedBeam();
BA_CORE_API_ GISASSimulation* RectDetectorPerpToReflectedBeamDpos();
BA_CORE_API_ GISASSimulation* MiniGISASMonteCarlo();
BA_CORE_API_ GISASSimulation* SphericalDetWithRoi();
BA_CORE_API_ GISASSimulation* RectDetWithRoi();
BA_CORE_API_ GISASSimulation* ConstantBackgroundGISAS();
BA_CORE_API_ GISASSimulation* MiniGISASFit();

// Specular simulation tests:
BA_CORE_API_ SpecularSimulation* BasicSpecular();
BA_CORE_API_ SpecularSimulation* SpecularWithGaussianBeam();
BA_CORE_API_ SpecularSimulation* SpecularWithSquareBeam();
BA_CORE_API_ SpecularSimulation* SpecularDivergentBeam();

// OffSpec simulations
BA_CORE_API_ OffSpecSimulation* MiniOffSpec();

// Depth probe simulations
BA_CORE_API_ DepthProbeSimulation* BasicDepthProbe();

} // namespace StandardSimulations

#endif // STANDARDSIMULATIONS_H
