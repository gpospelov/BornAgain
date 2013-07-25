#ifndef SAMPLEBUILDERFACTORY_H
#define SAMPLEBUILDERFACTORY_H

#include "IFactory.h"
#include "ISampleBuilder.h"

//! Factory to create standard pre-defined samples

class SampleBuilderFactory : public IFactory<std::string, ISampleBuilder>
{
 public:
    SampleBuilderFactory();

    ISample *createSample(const std::string& name);
    ISampleBuilder *createBuilder(const std::string& name);
};



#endif // SAMPLEBUILDERFACTORY_H
