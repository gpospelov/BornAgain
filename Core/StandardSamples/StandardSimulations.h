// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/StandardSimulations.h
//! @brief     Defines namespace and functions for standard simulations.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDSIMULATIONS_H
#define STANDARDSIMULATIONS_H


class Simulation;

//! Standard pre-defined simulations.

namespace StandardSimulations{

Simulation *IsGISAXS01();
Simulation *IsGISAXS02();
Simulation *IsGISAXS03BA();
Simulation *IsGISAXS03DWBA();
Simulation *IsGISAXS03BAsize();
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
Simulation *gui_IsGISAXS01();
Simulation *gui_IsGISAXS041DDL();
Simulation *gui_IsGISAXS042DDL();
Simulation *gui_IsGISAXS11();
Simulation *gui_IsGISAXS06L1();

}


#endif

