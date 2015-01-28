// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SampleBuilderFactory.cpp
//! @brief     Implement class SampleBuilderFactory.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleBuilderFactory.h"
#include "IsGISAXS01Builder.h"
#include "IsGISAXS02Builder.h"
#include "IsGISAXS03Builder.h"
#include "IsGISAXS04Builder.h"
#include "IsGISAXS06Builder.h"
#include "IsGISAXS07Builder.h"
#include "IsGISAXS08Builder.h"
#include "IsGISAXS09Builder.h"
#include "IsGISAXS10Builder.h"
#include "IsGISAXS11Builder.h"
#include "IsGISAXS15Builder.h"
#include "MesoCrystal01Builder.h"
#include "MultipleLayoutBuilder.h"
#include "PolarizedDWBAMagCylindersBuilder.h"
#include "LayerRoughnessBuilder.h"
#include "Ripple2Builder.h"
#include "Ripple1Builder.h"

SampleBuilderFactory::SampleBuilderFactory()
{

    registerItem(
        "isgisaxs01",
        IFactoryCreateFunction<IsGISAXS01Builder, ISampleBuilder>,
        "Mixture of cylinders and prisms without interference");

    registerItem(
        "isgisaxs02",
        IFactoryCreateFunction<IsGISAXS02Builder, ISampleBuilder>,
        "Mixture cylinder particles with different size distribution ");

    registerItem(
        "isgisaxs03_ba",
        IFactoryCreateFunction<IsGISAXS03BABuilder, ISampleBuilder>,
        "Cylinder formfactor in BA");
    registerItem(
        "isgisaxs03_dwba",
        IFactoryCreateFunction<IsGISAXS03DWBABuilder, ISampleBuilder>,
        "Cylinder formfactor in DWBA");
    registerItem(
        "isgisaxs03_basize",
        IFactoryCreateFunction<IsGISAXS03BASizeBuilder, ISampleBuilder>,
        "Cylinder formfactor in BA with size distribution");

    registerItem(
        "isgisaxs04_1DDL",
        IFactoryCreateFunction<IsGISAXS04Para1DBuilder, ISampleBuilder>,
        "IsGISAXS04 example, 1DDL structure factor");
    registerItem(
        "isgisaxs04_2DDL",
        IFactoryCreateFunction<IsGISAXS04Para2DBuilder, ISampleBuilder>,
        "IsGISAXS04 example, 2DDL structure factor");

    registerItem(
        "isgisaxs06a",
        IFactoryCreateFunction<IsGISAXS06Lattice1Builder, ISampleBuilder>,
        "2D lattice with disorder");
    registerItem(
        "isgisaxs06b",
        IFactoryCreateFunction<IsGISAXS06Lattice2Builder, ISampleBuilder>,
        "2D lattice centered");
    registerItem(
        "isgisaxs06c",
        IFactoryCreateFunction<IsGISAXS06Lattice3Builder, ISampleBuilder>,
        "2D lattice rotated");
    registerItem(
        "isgisaxs06d",
        IFactoryCreateFunction<IsGISAXS06Lattice4Builder, ISampleBuilder>,
        "2D lattice variants");

    registerItem(
        "isgisaxs07",
        IFactoryCreateFunction<IsGISAXS07Builder, ISampleBuilder>,
        "Mixture of different particles a la IsGISAXS morphology file");

    registerItem(
        "isgisaxs08a",
        IFactoryCreateFunction<IsGISAXS08ABuilder, ISampleBuilder>,
        "2DDL paracrystal lattice");

    registerItem(
        "isgisaxs08b",
        IFactoryCreateFunction<IsGISAXS08BBuilder, ISampleBuilder>,
        "2D paracrystal lattice with isotropic pdfs");

    registerItem(
        "isgisaxs09a",
        IFactoryCreateFunction<IsGISAXS09ABuilder, ISampleBuilder>,
        "Pyramids on top of substrate");
    registerItem(
        "isgisaxs09b",
        IFactoryCreateFunction<IsGISAXS09BBuilder, ISampleBuilder>,
        "Rotated pyramids on top of substrate");

    registerItem(
        "isgisaxs10",
        IFactoryCreateFunction<IsGISAXS10Builder, ISampleBuilder>,
        "Cylinders on top of substrate with interference");

    registerItem(
        "isgisaxs11",
        IFactoryCreateFunction<IsGISAXS11Builder, ISampleBuilder>,
        "Core shell nanoparticles");

    registerItem(
        "isgisaxs15",
        IFactoryCreateFunction<IsGISAXS15Builder, ISampleBuilder>,
        "Size spacing correlation approximation");

    registerItem(
        "mesocrystal01",
        IFactoryCreateFunction<MesoCrystal01Builder, ISampleBuilder>,
        "Mesocrystals of cylindrical shape composed by spherical nanoparticles");

    registerItem(
        "polmagcylinders1",
        IFactoryCreateFunction<PolarizedDWBAMagCylinders1Builder, ISampleBuilder>,
        "Polarized DWBA with zero magnetic field");
    registerItem(
        "polmagcylinders2",
        IFactoryCreateFunction<PolarizedDWBAMagCylinders2Builder, ISampleBuilder>,
        "Polarized DWBA with non-zero magnetic field");

    registerItem(
        "LayerWithRoughness",
        IFactoryCreateFunction<LayerRoughnessBuilder, ISampleBuilder>,
        "Layer with correlated roughness");

    registerItem(
       "multiple_layouts",
       IFactoryCreateFunction<MultipleLayoutBuilder, ISampleBuilder>,
      "cylinder and prisms using multiple layouts");

    registerItem(
        "ripple2",
        IFactoryCreateFunction<Ripple2Builder, ISampleBuilder>,
        "triangular ripple within the 1D-paracrystal model");

    registerItem(
        "ripple1",
        IFactoryCreateFunction<Ripple1Builder, ISampleBuilder>,
        "cosine ripple within the 1D-paracrystal model");

}


ISample *SampleBuilderFactory::createSample(const std::string& name)
{
    SampleBuilder_t builder(createItem(name));
    ISample *result = builder->buildSample();
    result->setName(name);
    return result;
}


SampleBuilder_t SampleBuilderFactory::createBuilder(const std::string& name)
{
    SampleBuilder_t result(createItem(name));
    result->setName(name);
    return result;
}
