// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Std/StandardTestInfo.h
//! @brief     Defines class StandardTestInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_STD_STANDARDTESTINFO_H
#define BORNAGAIN_TESTS_FUNCTIONAL_STD_STANDARDTESTINFO_H

#include "Wrap/WinDllMacros.h"
#include <string>
#include <vector>

//! @class StandardTestInfo
//! @ingroup standard_samples
//! @brief Collection of parameters necessary to run standard functional test.

class BA_CORE_API_ StandardTestInfo
{
public:
    StandardTestInfo();
    StandardTestInfo(const std::string& test_name, const std::string& test_description,
                     const std::string& simulation_name, const std::string& sample_builder_name,
                     double threshold);
    StandardTestInfo(const std::string& test_name, const std::string& test_description,
                     std::initializer_list<std::string> simulation_names,
                     std::initializer_list<std::string> sample_builder_names, double threshold);

    size_t size() const;

    std::string m_test_name;
    std::string m_test_description;
    std::vector<std::string> m_simulation_names;
    std::vector<std::string> m_sample_builder_names;
    double m_threshold;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_STD_STANDARDTESTINFO_H
