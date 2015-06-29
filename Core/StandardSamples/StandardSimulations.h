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


class GISASSimulation;

//! Standard pre-defined simulations.

namespace StandardSimulations{

//GISASSimulation *IsGISAXS01();
//GISASSimulation *IsGISAXS02();
//GISASSimulation *CylindersInBA();
//GISASSimulation *CylindersInDWBA();
//GISASSimulation *CylindersWithSizeDistribution();
//GISASSimulation *IsGISAXS041DDL();
//GISASSimulation *IsGISAXS042DDL();
//GISASSimulation *IsGISAXS06L1();
//GISASSimulation *IsGISAXS06L2();
//GISASSimulation *IsGISAXS06L3();
//GISASSimulation *IsGISAXS06L4();
//GISASSimulation *IsGISAXS07();
//GISASSimulation *IsGISAXS08a();
//GISASSimulation *IsGISAXS08b();
//GISASSimulation *IsGISAXS09a();
//GISASSimulation *IsGISAXS09b();
//GISASSimulation *IsGISAXS10();
//GISASSimulation *IsGISAXS11();
//GISASSimulation *IsGISAXS15();
//GISASSimulation *MesoCrystal01();
//GISASSimulation *PolarizedDWBAMagCylinders1();
//GISASSimulation *PolarizedDWBAMagCylinders2();
//GISASSimulation *LayerWithRoughness();
//GISASSimulation *Ripple2();
//GISASSimulation *Ripple1();
//GISASSimulation *gui_MultipleLayouts();

// toward functional tests refactoring
GISASSimulation *BasicGISAS();
GISASSimulation *MiniGISAS();
GISASSimulation *MiniGISASBeamDivergence();
GISASSimulation *MiniGISASDetectorResolution();
GISASSimulation *MiniGISASForMeso();
GISASSimulation *IsGISAXSSimulation1();
GISASSimulation *IsGISAXSSimulation2();


}


#endif

