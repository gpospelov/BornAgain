#include "SampleBuilderFactory.h"
#include "IsGISAXS01Builder.h"

SampleBuilderFactory::SampleBuilderFactory()
{

    registerItem(
        "isgisaxs01",
        IFactoryCreateFunction<IsGISAXS01Builder, ISampleBuilder>,
        "IsGISAXS01 example");
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
