#include "AdvancedFunctionalTestRegistry.h"
#include "Exceptions.h"
#include "Utils.h"

AdvancedFunctionalTestInfo::AdvancedFunctionalTestInfo()
    : m_threshold(0.0)
{

}

AdvancedFunctionalTestInfo::AdvancedFunctionalTestInfo(const std::string &test_name,
                                                       const std::string &test_description,
                                                       const std::string &simulation_name,
                                                       const std::string &sample_builder_name,
                                                       const std::string &component_registry_name,
                                                       double threshold)
    : m_test_name(test_name)
    , m_test_description(test_description)
    , m_simulation_name(simulation_name)
    , m_sample_builder_name(sample_builder_name)
    , m_component_registry_name(component_registry_name)
    , m_threshold(threshold)

{
}

AdvancedFunctionalTestRegistry::AdvancedFunctionalTestRegistry()
{

    add("IsGISAXS01",
        "Mixture of cylinders and prisms without interference",
        "IsGISAXSSimulation1",
        "isgisaxs01",
        "None",
        2e-10);

    add("FormFactors",
        "Test of all form factors defined",
        "BasicGISAS",
        "ParticleInTheAirBuilder",
        "FormFactorsRegistry",
        2e-10);

}

void AdvancedFunctionalTestRegistry::add(const std::string &test_name,
                                         const std::string &test_description,
                                         const std::string &simulation_name,
                                         const std::string &sample_builder_name,
                                         const std::string &component_registry_name,
                                         double threshold)
{
    catalogue_t::iterator it = m_catalogue.find(test_name);
    if( it != m_catalogue.end() ) {
        throw ExistingClassRegistrationException("AdvancedFunctionalTestRegistry::register_test_info() -> "
                                                 "Error. Existing item " + test_name);
    }
    m_catalogue[test_name] = AdvancedFunctionalTestInfo(test_name,
                                                        test_description,
                                                        simulation_name,
                                                        sample_builder_name,
                                                        component_registry_name,
                                                        threshold);
}

AdvancedFunctionalTestInfo AdvancedFunctionalTestRegistry::getTestInfo(const std::string &test_name)
{
    catalogue_t::iterator it = m_catalogue.find(test_name);
    if( it == m_catalogue.end() ) {
        throw ExistingClassRegistrationException("AdvancedFunctionalTestRegistry::getTestInfo() -> "
                                                 "Error. Item not found " + test_name);
    }

    return m_catalogue[test_name];
}

std::vector<std::string> AdvancedFunctionalTestRegistry::getTestNames() const
{
    std::vector<std::string> result;
    for(catalogue_t::const_iterator it = m_catalogue.begin(); it != m_catalogue.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

void AdvancedFunctionalTestRegistry::printCatalogue(std::ostream &ostr)
{
    for(catalogue_t::const_iterator it = m_catalogue.begin(); it != m_catalogue.end(); ++it) {
        AdvancedFunctionalTestInfo info = it->second;
        ostr << Utils::AdjustStringLength(info.m_test_name, 20) << " | ";
        ostr << Utils::AdjustStringLength(info.m_test_description, 40) << " | ";
        ostr << info.m_simulation_name << ", ";
        ostr << info.m_sample_builder_name << ", ";
        ostr << info.m_component_registry_name;
        ostr << "\n";
    }

}

bool AdvancedFunctionalTestRegistry::isValidTest(const std::string &test_name)
{
    return find(test_name) != end();
}



