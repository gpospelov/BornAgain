// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/StandardSamples.h
//! @brief     Defines namespace StandardSamples.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"

//! Collection of ISample* pointers to all standard examples.

namespace StandardSamples{

ISample *AirOnSubstrate();
ISample *SubstrateOnSubstrate();
ISample *SimpleMultilayer();
ISample *MultilayerOffspecTestcase1a();
ISample *MultilayerOffspecTestcase1b();
ISample *MultilayerOffspecTestcase2a();
ISample *MultilayerOffspecTestcase2b();
ISample *MultilayerSpecularMagneticTestCase();
ISample *PolarizedDWBATestCase();
//ISample *PolarizedDWBAZeroMagTestCase();

ISample *IsGISAXS7_morphology();
ISample *IsGISAXS8_2DDL_lattice();
ISample *IsGISAXS8_2DDL_lattice2();

ISample *IsGISAXS10_CylindersParacrystal1D();
ISample *IsGISAXS11_CoreShellParticles();
ISample *IsGISAXS14_LayeredSpheresOnGradedInterface();
ISample *IsGISAXS15_SSCA();
ISample *MesoCrystal1();
ISample *MesoCrystal2();
ISample *FormFactor_Box();
ISample *FormFactor_Cone();
ISample *FormFactor_Sphere();
ISample *FormFactor_Ellipsoid();
ISample *FormFactor_FullSpheroid();
ISample *FormFactor_HemiSpheroid();
ISample *FormFactor_Parallelpiped();
ISample *FormFactor_Cylinder();
ISample *FormFactor_Pyramid();
ISample *FormFactor_FullSphere();
ISample *FormFactor_Prism3();

}
#endif // STANDARDSAMPLES_H


