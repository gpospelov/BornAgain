// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestRegistry.cpp
//! @brief     Implements class FunctionalTestRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestRegistry.h"
#include "Exceptions.h"
#include "Utils.h"


FunctionalTestRegistry::FunctionalTestRegistry()
{

    add("FormFactors",
        "Test of all form factors defined",
        "GISASSmallDet",
        "ParticleInTheAirBuilder",
        "FormFactorsRegistry",
        2e-10);

    add("CylindersAndPrisms",
        "Mixture of cylinders and prisms without interference",
        "GISASSmallDet",
        "CylindersAndPrismsBuilder",
        "None",
        2e-10);

}

void FunctionalTestRegistry::add(const std::string &test_name,
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
    m_catalogue[test_name] = FunctionalTestInfo(test_name,
                                                        test_description,
                                                        simulation_name,
                                                        sample_builder_name,
                                                        component_registry_name,
                                                        threshold);
}

FunctionalTestInfo FunctionalTestRegistry::getTestInfo(const std::string &test_name)
{
    catalogue_t::iterator it = m_catalogue.find(test_name);
    if( it == m_catalogue.end() ) {
        throw ExistingClassRegistrationException("AdvancedFunctionalTestRegistry::getTestInfo() -> "
                                                 "Error. Item not found " + test_name);
    }

    return m_catalogue[test_name];
}

void FunctionalTestRegistry::printCatalogue(std::ostream &ostr)
{
    for(catalogue_t::const_iterator it = m_catalogue.begin(); it != m_catalogue.end(); ++it) {
        FunctionalTestInfo info = it->second;
        ostr << Utils::AdjustStringLength(info.m_test_name, 20) << " | ";
        ostr << Utils::AdjustStringLength(info.m_test_description, 40) << " | ";
        ostr << info.m_simulation_name << ", ";
        ostr << info.m_sample_builder_name << ", ";
        ostr << info.m_component_registry_name;
        ostr << "\n";
    }

}

bool FunctionalTestRegistry::isValidTest(const std::string &test_name)
{
    return find(test_name) != end();
}



