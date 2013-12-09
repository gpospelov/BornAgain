#include "FunctionalTestRegistry.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>

FunctionalTestRegistry::Catalogue FunctionalTestRegistry::m_catalogue = FunctionalTestRegistry::Catalogue();


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
    m_data[name] = FunctionalTestInfo(name, description, reference, threshold);
}


void FunctionalTestRegistry::Catalogue::print()
{
    std::cout << "--- FunctionalTestRegistry::Catalogue::print() ---" << std::endl;
    for(catalogue_t::iterator it = m_data.begin(); it!= m_data.end(); ++it) {
        FunctionalTestInfo &info = (*it).second;
        std::cout << std::setw(12) << std::left << info.m_name << " | "
                  << std::setw(24) << std::left << info.m_description << " | "
                  << std::setw(12) << std::left << info.m_reference_file << " | "
                  << std::setw(6) << std::left  << info.m_threshold << std::endl;
    }
}


FunctionalTestInfo FunctionalTestRegistry::Catalogue::getInfo(const std::string &name)
{
    catalogue_t::iterator it = m_data.find(name);
    if( it == m_data.end() ) {
        std::ostringstream ostr;
        ostr << "FunctionalTestRegistry::Catalogue::getInfo() -> Error. "
             << "Not existing test name '" << name << "'. "
             << "Existing items are:" << std::endl;
        for(catalogue_t::iterator it2 = m_data.begin(); it2!=m_data.end(); ++it2) {
            ostr << (*it2).first << std::endl;
        }
        throw ExistingClassRegistrationException(ostr.str());
    }
    return m_data[name];
}


bool FunctionalTestRegistry::isRegisteredName(const std::string &name)
{
    if( m_catalogue.m_data.find(name) == m_catalogue.m_data.end() ) {
        return false;
    } else {
        return true;
    }
}


FunctionalTest_t FunctionalTestRegistry::runTest(const std::string &name)
{
    FunctionalTest_t test(new FunctionalTest(m_catalogue.getInfo(name)));
    test->runTest();
    return test;
}


int FUNCTIONAL_TEST(const std::string &name)
{
    FunctionalTestRegistry registry;
    FunctionalTest_t test = registry.runTest(name);
    return test->analyseResults();
}


