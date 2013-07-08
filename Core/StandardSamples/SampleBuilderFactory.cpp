#include "SampleBuilderFactory.h"
#include "IsGISAXS01Builder.h"
#include "IsGISAXS02Builder.h"
#include "IsGISAXS04Builder.h"

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
        "isgisaxs04_1DDL",
        IFactoryCreateFunction<IsGISAXS04Para1DBuilder, ISampleBuilder>,
        "IsGISAXS04 example, 1DDL structure factor");

    registerItem(
        "isgisaxs04_2DDL",
        IFactoryCreateFunction<IsGISAXS04Para2DBuilder, ISampleBuilder>,
        "IsGISAXS04 example, 2DDL structure factor");

}


ISample *SampleBuilderFactory::createSample(const std::string& name)
{
    ISampleBuilder *builder = createItem(name);
    ISample *result = builder->buildSample();
    delete builder;
    return result;
}


ISampleBuilder *SampleBuilderFactory::createBuilder(const std::string& name)
{
    ISampleBuilder *result = createItem(name);
    return result;
}
