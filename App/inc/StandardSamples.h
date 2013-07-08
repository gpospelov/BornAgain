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
//ISample *IsGISAXS1_CylinderAndPrism();
//ISample *IsGISAXS2_CylindersMixture();
ISample *IsGISAXS3_CylinderDWBA();
ISample *IsGISAXS3_CylinderBA();
ISample *IsGISAXS3_CylinderBASize();
//ISample *IsGISAXS4_1DDL();
//ISample *IsGISAXS4_2DDL();
ISample *IsGISAXS6_lattice();
ISample *IsGISAXS6_centered();
ISample *IsGISAXS6_rotated();
ISample *IsGISAXS7_morphology();
ISample *IsGISAXS8_2DDL_lattice();
ISample *IsGISAXS8_2DDL_lattice2();
ISample *IsGISAXS9_Pyramid();
ISample *IsGISAXS9_RotatedPyramid();
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


