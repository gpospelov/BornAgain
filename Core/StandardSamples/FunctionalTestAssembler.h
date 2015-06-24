#ifndef FUNCTIONALTESTASSEMBLER_H
#define FUNCTIONALTESTASSEMBLER_H

#include "WinDllMacros.h"
#include "FunctionalTestRegistry.h"
#include <string>

class IFunctionalTest;

class FunctionalTestAssembler
{
public:

    IFunctionalTest *getTest(const std::string &test_name);

    bool isValidTest(const std::string &test_name);

    void printCatalogue() const;

private:
    static FunctionalTestRegistry m_catalogue;
};

//! run functional tests with given name
BA_CORE_API_ int ADVANCED_FUNCTIONAL_TEST(const std::string &test_name);

#endif
