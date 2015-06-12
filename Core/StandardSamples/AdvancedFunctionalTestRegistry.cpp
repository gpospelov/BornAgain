#include "AdvancedFunctionalTestRegistry.h"
#include "Exceptions.h"

AdvancedFunctionalTestInfo::AdvancedFunctionalTestInfo()
    : m_threshold(0.0)
{

}

AdvancedFunctionalTestInfo::AdvancedFunctionalTestInfo(const std::string &test_name,
                                                       const std::string &test_description,
                                                       const std::string &simulation_name,
                                                       const std::string &sample_builder_name,
                                                       const std::string &component_variator_name,
                                                       double threshold)
    : m_test_name(test_name)
    , m_test_description(test_description)
    , m_simulation_name(simulation_name)
    , m_sample_builder_name(sample_builder_name)
    , m_component_variator_name(component_variator_name)
    , m_threshold(threshold)

{
}

AdvancedFunctionalTestRegistry::AdvancedFunctionalTestRegistry()
{

    add("isgisaxs01",
        "Mixture of cylinders and prisms without interference",
        "BasicGISAS",
        "isgisaxs01",
        "DefaultVariator",
        2e-10);

//    add("MyFirstTest",
//        "Some description",
//        "BasicGISAS",
//        "ParticleInTheAirBuilder",
//        "DefaultVariator",
//        1e-12
//    );

}

void AdvancedFunctionalTestRegistry::add(const std::string &test_name,
                                         const std::string &test_description,
                                         const std::string &simulation_name,
                                         const std::string &sample_builder_name,
                                         const std::string &component_locator_name,
                                         double m_threshold)
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
                                                        component_locator_name,
                                                        m_threshold);
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



