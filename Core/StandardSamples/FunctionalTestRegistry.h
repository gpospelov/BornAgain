// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestRegistry.h
//! @brief     Defines class FunctionalTestRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTREGISTRY_H
#define FUNCTIONALTESTREGISTRY_H

#include "WinDllMacros.h"
#include "FunctionalTestInfo.h"
#include <vector>
#include <string>
#include <map>

//! @class FunctionalTestRegistry
//! @ingroup standard_samples
//! @brief The registry which holds information about available functional tests.

class BA_CORE_API_ FunctionalTestRegistry
{
public:

    typedef std::map<std::string, FunctionalTestInfo> catalogue_t;
    typedef catalogue_t::iterator iterator;
    typedef catalogue_t::const_iterator const_iterator;

    FunctionalTestRegistry();

    void add(const std::string &test_name,
             const std::string &test_description,
             const std::string &simulation_name,
             const std::string &sample_builder_name,
             const std::string &component_registry_name,
             double threshold);

    FunctionalTestInfo getTestInfo(const std::string &test_name);

    iterator begin() { return m_catalogue.begin(); }
    iterator end() { return m_catalogue.end(); }
    iterator find(const std::string &key) { return m_catalogue.find(key); }

    void printCatalogue(std::ostream &ostr);

    bool isValidTest(const std::string &test_name);

private:
    catalogue_t m_catalogue;
};

#endif
