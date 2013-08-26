#ifndef SAMPLEBUILDERFACTORY_H
#define SAMPLEBUILDERFACTORY_H

#include "WinDllMacros.h"
#include "IFactory.h"
#include "ISampleBuilder.h"

//! Factory to create standard pre-defined samples

class BA_CORE_API_ SampleBuilderFactory : public IFactory<std::string, ISampleBuilder>
{
 public:
    SampleBuilderFactory();

    ISample *createSample(const std::string& name);
    ISampleBuilder *createBuilder(const std::string& name);
};



#endif // SAMPLEBUILDERFACTORY_H
