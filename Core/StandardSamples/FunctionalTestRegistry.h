#ifndef FUNCTIONALTESTREGISTRY_H
#define FUNCTIONALTESTREGISTRY_H


#include <string>
#include <map>
#include "IFunctionalTest.h"

class FunctionalTestRegistry
{
public:

    class Catalogue
    {
    public:
        typedef std::map<std::string, FunctionalTestInfo> catalogue_t;
        Catalogue();
        void add(const std::string &name, const std::string &description,
                 const std::string &reference, double threshold);
        void print();
        catalogue_t m_data;
        FunctionalTestInfo getInfo(const std::string &name);
    };

    void printCatalogue() { m_catalogue.print(); }

    FunctionalTest_t getTest(const std::string &name);

    //FunctionalTest_t runTest(const std::string &name);

    bool isRegisteredName(const std::string &name);

private:

    static Catalogue m_catalogue;
};


//! run functional tests with given name
int FUNCTIONAL_TEST(const std::string &name);



#endif
