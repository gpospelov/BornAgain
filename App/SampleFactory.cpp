// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/SampleFactory.cpp
//! @brief     Implements class SampleFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleFactory.h"
#include "Exceptions.h"
#include "StandardSamples.h"

#include <iostream>

/* test for remote git access */

SampleFactory::SampleFactory()
{
    //setOwnObjects(true); //factory will take care about samples
    setOwnObjects(false);

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

    // IsGISAXS15 example: Size-Spacing Correlation Approximation
//    registerItem("IsGISAXS15_SSCA", StandardSamples::IsGISAXS15_SSCA);

    // mesocrystal's
//    registerItem("MesoCrystal1", StandardSamples::MesoCrystal1);
//    registerItem("MesoCrystal2", StandardSamples::MesoCrystal2);

//    registerItem("PolarizedDWBATestCase", StandardSamples::PolarizedDWBATestCase);


//    registerItem("FormFactor_Box", StandardSamples::FormFactor_Box);
//    registerItem("FormFactor_Cone", StandardSamples::FormFactor_Cone);
//    registerItem("FormFactor_TruncatedSphere", StandardSamples::FormFactor_TruncatedSphere);
//    registerItem("FormFactor_EllipsoidalCylinder", StandardSamples::FormFactor_EllipsoidalCylinder);
//    registerItem("FormFactor_FullSpheroid", StandardSamples::FormFactor_FullSpheroid);
//    registerItem("FormFactor_HemiEllipsoid", StandardSamples::FormFactor_HemiEllipsoid;
//    registerItem("FormFactor_Parallelepiped", StandardSamples::FormFactor_Parallelpiped);
//    registerItem("FormFactor_Cylinder", StandardSamples::FormFactor_Cylinder);
//    registerItem("FormFactor_Pyramid", StandardSamples::FormFactor_Pyramid);
//    registerItem("FormFactor_FullSphere", StandardSamples::FormFactor_FullSphere);
//    registerItem("FormFactor_Prism3", StandardSamples::FormFactor_Prism3);
}


