#ifndef FUNCTIONALTESTREGISTRY_H
#define FUNCTIONALTESTREGISTRY_H


#include <string>
#include <map>

class FunctionalTestRegistry
{
public:

    class TestInfo
    {
    public:
        TestInfo()
            : m_threshold(0) {  }

        TestInfo(const std::string &name, const std::string &description,
                  const std::string &reference, double threshold )
            : m_name(name)
            , m_description(description)
            , m_reference(reference)
            , m_threshold(threshold) {  }

        void print();
        std::string m_name;
        std::string m_description;
        std::string m_reference;
        double m_threshold;
    };

    class Catalogue
    {
    public:
        typedef std::map<std::string, TestInfo> catalogue_t;
        Catalogue();
        void add(const std::string &name, const std::string &description,
                 const std::string &reference, double threshold);
        void print();
        catalogue_t m_data;
        TestInfo getInfo(const std::string &name);
    };

    void printCatalogue() { m_catalogue.print(); }

    int runTest(const std::string &name);

    bool isRegisteredName(const std::string &name);


private:

    static Catalogue m_catalogue;
};


//! run functional tests with given name
int FUNCTIONAL_TEST(const std::string &name);



#endif
