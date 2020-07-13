// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestCatalog.h
//! @brief     Defines class StandardTestCatalog.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_STANDARDTESTCATALOG_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_STANDARDTESTCATALOG_H

#include "Tests/Functional/TestMachinery/StandardTestInfo.h"
#include "Wrap/WinDllMacros.h"
#include <map>

//! @class StandardTestCatalog
//! @ingroup standard_samples
//! @brief Catalog with the description of standard functional tests.

class BA_CORE_API_ StandardTestCatalog
{
public:
    StandardTestCatalog();

    StandardTestInfo testInfo(const std::string& test_name);

    bool contains(const std::string& test_name);

private:
    void add(const std::string& test_name, const std::string& test_description,
             const std::string& simulation_name, const std::string& sample_builder_name,
             double threshold);

    void add(const std::string& test_name, const std::string& test_description,
             std::initializer_list<std::string> simulation_names,
             std::initializer_list<std::string> sample_builder_name, double threshold);

    std::map<std::string, StandardTestInfo> m_catalog;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_STANDARDTESTCATALOG_H
