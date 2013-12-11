// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/SampleFactory.cpp
//! @brief     Implements class SampleFactory.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleFactory.h"
#include "Exceptions.h"
#include "StandardSamples.h"

#include <iostream>

/* test for remote git access */

SampleFactory::SampleFactory()
{
    setOwnObjects(true); //factory will take care about samples

    // samples used for reflection/transmission coefficients validation
    registerItem("AirOnSubstrate", StandardSamples::AirOnSubstrate);
    registerItem("SubstrateOnSubstrate", StandardSamples::SubstrateOnSubstrate);
    registerItem("SimpleMultilayer", StandardSamples::SimpleMultilayer);

    // samples used for off-specular reflectivity validation

    // 10x2 layers for comparison of diffuse (off-specular) reflectivity with
    // and without cross-correlation in layers' roughnesses
    registerItem("MultilayerOffspecTestcase1a",
            StandardSamples::MultilayerOffspecTestcase1a);
    registerItem("MultilayerOffspecTestcase1b",
            StandardSamples::MultilayerOffspecTestcase1b);

    // thin layer of air (two different thicknesses) to check diffuse
    // (off-specular) reflectivity
    registerItem("MultilayerOffspecTestcase2a",
            StandardSamples::MultilayerOffspecTestcase2a);
    registerItem("MultilayerOffspecTestcase2b",
            StandardSamples::MultilayerOffspecTestcase2b);

    // 10x2 layers with same index of refraction but opposite magnetization
    registerItem("MultilayerSpecularMagneticTestCase",
            StandardSamples::MultilayerSpecularMagneticTestCase);

    // magnetic cylinders on substrate for polarized DWBA
    registerItem("PolarizedDWBATestCase",
            StandardSamples::PolarizedDWBATestCase);

    // cylinder DWBA form factor with matrix calculation
 //   registerItem("PolarizedDWBAZeroMagTestCase",
 //           StandardSamples::PolarizedDWBAZeroMagTestCase);

    // IsGISAXS7 example: particle mixture from morphology file
    registerItem("IsGISAXS7_mor", StandardSamples::IsGISAXS7_morphology);

    // IsGISAXS8 example: cylinders on top of substrate with paracrystal lattice structure
    registerItem("IsGISAXS8_2DDL_lattice", StandardSamples::IsGISAXS8_2DDL_lattice);
    registerItem("IsGISAXS8_2DDL_lattice2", StandardSamples::IsGISAXS8_2DDL_lattice2);

    // IsGISAXS9 example: pyramid and rotated pyramid
//    registerItem("IsGISAXS9_Pyramid", StandardSamples::IsGISAXS9_Pyramid);
//    registerItem("IsGISAXS9_RotatedPyramid", StandardSamples::IsGISAXS9_RotatedPyramid);

    // IsGISAXS10 example: cylinders with interference
    registerItem("IsGISAXS10_CylindersParacrystal1D", StandardSamples::IsGISAXS10_CylindersParacrystal1D);

    // IsGISAXS11 example: core shell parallelepipeds
    registerItem("IsGISAXS11_CoreShellParticle", StandardSamples::IsGISAXS11_CoreShellParticles);

    // IsGISAXS14 example: layered sphere on graded interface
    registerItem("IsGISAXS14_LayeredSpheresOnGradedInterface", StandardSamples::IsGISAXS14_LayeredSpheresOnGradedInterface);

    // IsGISAXS15 example: Size-Spacing Correlation Approximation
    registerItem("IsGISAXS15_SSCA", StandardSamples::IsGISAXS15_SSCA);

    // mesocrystal's
    registerItem("MesoCrystal1", StandardSamples::MesoCrystal1);
    registerItem("MesoCrystal2", StandardSamples::MesoCrystal2);

    registerItem("FormFactor_Box", StandardSamples::FormFactor_Box);
    registerItem("FormFactor_Cone", StandardSamples::FormFactor_Cone);
    registerItem("FormFactor_Sphere", StandardSamples::FormFactor_Sphere);
    registerItem("FormFactor_EllipsoidalCylinder", StandardSamples::FormFactor_EllipsoidalCylinder);
    registerItem("FormFactor_FullSpheroid", StandardSamples::FormFactor_FullSpheroid);
    registerItem("FormFactor_HemiEllipsoid", StandardSamples::FormFactor_HemiEllipsoid);
    registerItem("FormFactor_Parallelepiped", StandardSamples::FormFactor_Parallelpiped);
    registerItem("FormFactor_Cylinder", StandardSamples::FormFactor_Cylinder);
    registerItem("FormFactor_Pyramid", StandardSamples::FormFactor_Pyramid);
    registerItem("FormFactor_FullSphere", StandardSamples::FormFactor_FullSphere);
    registerItem("FormFactor_Prism3", StandardSamples::FormFactor_Prism3);
}


