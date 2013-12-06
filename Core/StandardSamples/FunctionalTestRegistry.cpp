#include "FunctionalTestRegistry.h"
#include "Exceptions.h"
#include <iostream>

FunctionalTestRegistry::Catalogue FunctionalTestRegistry::m_catalogue = FunctionalTestRegistry::Catalogue();


void FunctionalTestRegistry::TestInfo::print()
{
    std::cout << m_name << " " << m_description << " " << m_reference << " " << m_threshold << std::endl;
}


FunctionalTestRegistry::Catalogue::Catalogue()
{
    add("isgisaxs01",
        "Mixture of cylinders and prisms without interference",
        "isgisaxs01_reference.ima.gz", 2e-10);
}

void FunctionalTestRegistry::Catalogue::add(const std::string &name,
    const std::string &description, const std::string &reference, double threshold)
{
    catalogue_t::iterator it = m_data.find(name);
    if( it != m_data.end() ) {
        throw ExistingClassRegistrationException("FunctionalTestRegistry::Catalogue::add() -> "
                                                 "Error. Existing item " +name);
    }

    m_data[name] = TestInfo(name, description, reference, threshold);

}


void FunctionalTestRegistry::Catalogue::print()
{
    for(catalogue_t::iterator it = m_data.begin(); it!= m_data.end(); ++it) {
        (*it).second.print();
    }
}


int FunctionalTestRegistry::runTest(const std::string &name)
{

}


int FUNCTIONAL_TEST(const std::string &name)
{
    FunctionalTestRegistry tests;
    return tests.runTest(name);
}
