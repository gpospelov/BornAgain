#include "SampleFactory.h"
#include "Exceptions.h"
#include "StandardSamples.h"

#include <iostream>


SampleFactory::SampleFactory()
{
    setOwnObjects(true);

    // samples used for fresnel coefficients validation
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
    registerItem("IsGISAXS1_CylinderAndPrism", StandardSamples::IsGISAXS1_CylinderAndPrism);

    // IsGISAXS2 example: mixture of cylindrical particles with two size distribution
    registerItem("IsGISAXS2_CylindersMixture", StandardSamples::IsGISAXS2_CylindersMixture);

    // IsGISAXS3 example: cylinder on top of substrate, cylinder in the air, cylinder with size distribution
    registerItem("IsGISAXS3_CylinderDWBA", StandardSamples::IsGISAXS3_CylinderDWBA);
    registerItem("IsGISAXS3_CylinderBA", StandardSamples::IsGISAXS3_CylinderBA);
    registerItem("IsGISAXS3_CylinderBASize", StandardSamples::IsGISAXS3_CylinderBASize);

    // IsGISAXS9 example: pyramid and rotated pyramid
    registerItem("IsGISAXS9_Pyramid", StandardSamples::IsGISAXS9_Pyramid);
    registerItem("IsGISAXS9_RotatedPyramid", StandardSamples::IsGISAXS9_RotatedPyramid);

    // IsGISAXS10 example: cyliunderw with interference
    registerItem("IsGISAXS10_CylindersParacrystal1D", StandardSamples::IsGISAXS10_CylindersParacrystal1D);

    // mesocrystal's
    registerItem("MesoCrystal1", StandardSamples::MesoCrystal1);
    registerItem("MesoCrystal2", StandardSamples::MesoCrystal2);
}

