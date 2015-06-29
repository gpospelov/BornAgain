#ifndef OBSOLETEFUNCTIONALTESTREGISTRY_H
#define OBSOLETEFUNCTIONALTESTREGISTRY_H


#include <string>
#include <map>
#include "ObsoleteIFunctionalTest.h"

class BA_CORE_API_ ObsoleteFunctionalTestRegistry
{
public:

    class Catalogue
    {
    public:
        typedef std::map<std::string, ObsoleteFunctionalTestInfo> catalogue_t;
        Catalogue();
        void add(const std::string &name, const std::string &description,
                 const std::string &reference, double threshold, bool normalize = false);
        void print();
        catalogue_t m_data;
        ObsoleteFunctionalTestInfo getInfo(const std::string &name);
    };

    void printCatalogue() { m_catalogue.print(); }

    ObsoleteFunctionalTest* getTest(const std::string &name);

    bool isRegisteredName(const std::string &name);

private:

    static Catalogue m_catalogue;
};


//! run functional tests with given name
BA_CORE_API_ int FUNCTIONAL_TEST(const std::string &name);



#endif
