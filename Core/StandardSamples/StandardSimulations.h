// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/StandardSimulations.h
//! @brief     Defines namespace and functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDSIMULATIONS_H
#define STANDARDSIMULATIONS_H


class Simulation;

//! Standard pre-defined simulations.

namespace StandardSimulations{

Simulation *IsGISAXS01();
Simulation *IsGISAXS02();
Simulation *CylindersInBA();
Simulation *CylindersInDWBA();
Simulation *CylindersWithSizeDistribution();
Simulation *IsGISAXS041DDL();
Simulation *IsGISAXS042DDL();
Simulation *IsGISAXS06L1();
Simulation *IsGISAXS06L2();
Simulation *IsGISAXS06L3();
Simulation *IsGISAXS06L4();
Simulation *IsGISAXS07();
Simulation *IsGISAXS08a();
Simulation *IsGISAXS08b();
Simulation *IsGISAXS09a();
Simulation *IsGISAXS09b();
Simulation *IsGISAXS10();
Simulation *IsGISAXS11();
Simulation *IsGISAXS15();
Simulation *MesoCrystal01();
Simulation *PolarizedDWBAMagCylinders1();
Simulation *PolarizedDWBAMagCylinders2();
Simulation *LayerWithRoughness();
Simulation *Ripple2();
Simulation *Ripple1();
Simulation *gui_CylinderAndPrisms();
Simulation *gui_Interference1DParaCrystal();
Simulation *gui_Interference2DParaCrystal();
Simulation *gui_CoreShellParticles();
Simulation *gui_Interference2DSquareLattice();
Simulation *gui_Interference2DCenteredLattice();
Simulation *gui_RotatedPyramids();
Simulation *gui_MultipleLayouts();
Simulation *BeamDivergence();
Simulation *DetectorResolution();
Simulation *ParticleDistribution();
Simulation *gui_ParticleComposition();
}


#endif

