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
#include "PolarizedDWBAZeroMagBuilder.h"
#include "LayerRoughnessBuilder.h"

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
        "isgisaxs06_lattice1",
        IFactoryCreateFunction<IsGISAXS06Lattice1Builder, ISampleBuilder>,
        "2D lattice with disorder");
    registerItem(
        "isgisaxs06_lattice2",
        IFactoryCreateFunction<IsGISAXS06Lattice2Builder, ISampleBuilder>,
        "2D lattice centered");
    registerItem(
        "isgisaxs06_lattice3",
        IFactoryCreateFunction<IsGISAXS06Lattice3Builder, ISampleBuilder>,
        "2D lattice rotated");
    registerItem(
        "isgisaxs06_lattice4",
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
        "PolarizedDWBAZeroMag",
        IFactoryCreateFunction<PolarizedDWBAZeroMagBuilder, ISampleBuilder>,
        "Polarized DWBA with zero magnetic field");

    registerItem(
        "LayerWithRoughness",
        IFactoryCreateFunction<LayerRoughnessBuilder, ISampleBuilder>,
        "Layer with correlated roughness");

}


ISample *SampleBuilderFactory::createSample(const std::string& name)
{
    SampleBuilder_t builder(createItem(name));
    ISample *result = builder->buildSample();
    return result;
}


SampleBuilder_t SampleBuilderFactory::createBuilder(const std::string& name)
{
    SampleBuilder_t result(createItem(name));
    return result;
}
