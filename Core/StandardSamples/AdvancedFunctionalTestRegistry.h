// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/AdvancedFunctionalTestRegistry.h
//! @brief     Defines class AdvancedFunctionalTestRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ADVANCEDFUNCTIONALTESTREGISTRY_H
#define ADVANCEDFUNCTIONALTESTREGISTRY_H

#include "WinDllMacros.h"
#include <string>
#include <map>



class BA_CORE_API_ AdvancedFunctionalTestInfo
{
public:
    AdvancedFunctionalTestInfo();
    AdvancedFunctionalTestInfo(const std::string &test_name,
                               const std::string &test_description,
                               const std::string &simulation_name,
                               const std::string &sample_builder_name,
                               const std::string &component_registry_name,
                               double m_threshold);

    std::string m_test_name;
    std::string m_test_description;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
    std::string m_component_registry_name;
    double m_threshold;
};


//! @class AdvancedFunctionalTestRegistry
//! @ingroup standard_samples
//! @brief The registry which holds information about available functional tests.

class BA_CORE_API_ AdvancedFunctionalTestRegistry
{
public:

    typedef std::map<std::string, AdvancedFunctionalTestInfo> catalogue_t;

    AdvancedFunctionalTestRegistry();

    void add(const std::string &test_name,
             const std::string &test_description,
             const std::string &simulation_name,
             const std::string &sample_builder_name,
             const std::string &component_registry_name,
             double threshold);

    AdvancedFunctionalTestInfo getTestInfo(const std::string &test_name);

private:
    catalogue_t m_catalogue;
};




#endif
