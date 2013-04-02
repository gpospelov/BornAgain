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

    // samples used for Fresnel coefficients validation
    registerItem("AirOnSubstrate", StandardSamples::AirOnSubstrate);
    registerItem("SubstrateOnSubstrate", StandardSamples::SubstrateOnSubstrate);
    registerItem("SimpleMultilayer", StandardSamples::SimpleMultilayer);

    // samples used for offspecular reflectivity validation

    //10x2 layers for comparison of diffuse (off-specular) reflectivity with and without cross-correlation in layer's roughnesses
    registerItem("MultilayerOffspecTestcase1a", StandardSamples::MultilayerOffspecTestcase1a);
    registerItem("MultilayerOffspecTestcase1b", StandardSamples::MultilayerOffspecTestcase1b);

    // thin layer of air (two different thicknesses) to check diffuse (off-specular) reflectivity
    registerItem("MultilayerOffspecTestcase2a", StandardSamples::MultilayerOffspecTestcase2a);
    registerItem("MultilayerOffspecTestcase2b", StandardSamples::MultilayerOffspecTestcase2b);

    // IsGISAXS1 example: cylinder and prism
    //registerItem("IsGISAXS1_CylinderAndPrism", StandardSamples::IsGISAXS1_CylinderAndPrism);

    // IsGISAXS2 example: mixture of cylindrical particles with two size distribution
    registerItem("IsGISAXS2_CylindersMixture", StandardSamples::IsGISAXS2_CylindersMixture);

    // IsGISAXS3 example: cylinder on top of substrate, cylinder in the air, cylinder with size distribution
    registerItem("IsGISAXS3_CylinderDWBA", StandardSamples::IsGISAXS3_CylinderDWBA);
    registerItem("IsGISAXS3_CylinderBA", StandardSamples::IsGISAXS3_CylinderBA);
    registerItem("IsGISAXS3_CylinderBASize", StandardSamples::IsGISAXS3_CylinderBASize);

    // IsGISAXS4 example: cylinders on top of substrate with paracrystal structure factors
    registerItem("IsGISAXS4_1DDL", StandardSamples::IsGISAXS4_1DDL);
    registerItem("IsGISAXS4_2DDL", StandardSamples::IsGISAXS4_2DDL);

    // IsGISAXS6 example: cylinders with lattice interference function
    registerItem("IsGISAXS6_lattice", StandardSamples::IsGISAXS6_lattice);
    registerItem("IsGISAXS6_centered", StandardSamples::IsGISAXS6_centered);
    registerItem("IsGISAXS6_rotated", StandardSamples::IsGISAXS6_rotated);

    // IsGISAXS7 example: particle mixture from morphology file
    registerItem("IsGISAXS7_mor", StandardSamples::IsGISAXS7_morphology);

    // IsGISAXS8 example: cylinders on top of substrate with paracrystal lattice structure
    registerItem("IsGISAXS8_2DDL_lattice", StandardSamples::IsGISAXS8_2DDL_lattice);
    registerItem("IsGISAXS8_2DDL_lattice2", StandardSamples::IsGISAXS8_2DDL_lattice2);

    // IsGISAXS9 example: pyramid and rotated pyramid
    registerItem("IsGISAXS9_Pyramid", StandardSamples::IsGISAXS9_Pyramid);
    registerItem("IsGISAXS9_RotatedPyramid", StandardSamples::IsGISAXS9_RotatedPyramid);

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
    registerItem("FormFactor_Ellipsoid", StandardSamples::FormFactor_Ellipsoid);
    registerItem("FormFactor_FullSpheroid", StandardSamples::FormFactor_FullSpheroid);
    registerItem("FormFactor_HemiSpheroid", StandardSamples::FormFactor_HemiSpheroid);
    registerItem("FormFactor_Parallelpiped", StandardSamples::FormFactor_Parallelpiped);
    registerItem("FormFactor_Cylinder", StandardSamples::FormFactor_Cylinder);
    registerItem("FormFactor_Pyramid", StandardSamples::FormFactor_Pyramid);
    registerItem("FormFactor_FullSphere", StandardSamples::FormFactor_FullSphere);
    registerItem("FormFactor_Prism3", StandardSamples::FormFactor_Prism3);
}


