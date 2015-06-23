#ifndef FUNCTIONALTESTASSEMBLER_H
#define FUNCTIONALTESTASSEMBLER_H

#include "WinDllMacros.h"
#include "AdvancedFunctionalTestRegistry.h"
#include <string>

class IAdvancedFunctionalTest;

class FunctionalTestAssembler
{
public:

    IAdvancedFunctionalTest *getTest(const std::string &test_name);

    bool isValidTest(const std::string &test_name);

    void printCatalogue() const;

private:
    static AdvancedFunctionalTestRegistry m_catalogue;
};

//! run functional tests with given name
BA_CORE_API_ int ADVANCED_FUNCTIONAL_TEST(const std::string &test_name);

#endif
