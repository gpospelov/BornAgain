#ifndef STANDARDFITSFACTORY_H
#define STANDARDFITSFACTORY_H

#include "IFactory.h"
#include "IFutest.h"


//! @class StandardFitsFactory
//! @ingroup standard_samples
//! @brief Factory to create predefined functional fit tests

class BA_CORE_API_ StandardFitsFactory : public IFactory<IFutest>
{
public:
    StandardFitsFactory();

    IFutest *createTest(const std::string &test_name);

    bool isValidTest(const std::string &test_name);

    void printCatalogue(std::ostream &ostr);
};

#endif
