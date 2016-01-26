#ifndef STANDARDFITSFACTORY_H
#define STANDARDFITSFACTORY_H

#include "IFactory.h"
#include "IFunctionalTest.h"


//! @class StandardFitsFactory
//! @ingroup standard_samples
//! @brief Factory to create predefined functional fit tests

class BA_CORE_API_ StandardFitsFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    StandardFitsFactory();

    IFunctionalTest *createTest(const std::string &test_name);

    bool isValidTest(const std::string &test_name);

    void printCatalogue(std::ostream &ostr);

};


#endif
