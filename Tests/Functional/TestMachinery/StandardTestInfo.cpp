// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/SimulationInfo.cpp
//! @brief     Implements class SimulationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "StandardTestInfo.h"
#include <stdexcept>

StandardTestInfo::StandardTestInfo()
    : m_threshold(0.0)
{
}

StandardTestInfo::StandardTestInfo(const std::string& test_name,
                       const std::string& test_description,
                       const std::string& simulation_name,
                       const std::string& sample_builder_name,
                       double threshold)
    : m_test_name(test_name)
    , m_test_description(test_description)
    , m_simulation_name({simulation_name})
    , m_sample_builder_name({sample_builder_name})
    , m_threshold(threshold)
{
}

StandardTestInfo::StandardTestInfo(const std::string& test_name,
                 const std::string& test_description,
                 std::vector<std::string> simulation_names,
                 std::vector<std::string> sample_builder_names,
                 double threshold)
    : m_test_name(test_name)
    , m_test_description(test_description)
    , m_simulation_name(std::move(simulation_names))
    , m_sample_builder_name(std::move(sample_builder_names))
    , m_threshold(threshold)
{
    if (m_simulation_name.size() != m_sample_builder_name.size())
        throw std::runtime_error("Error in StandardTestInfo::size(): inconsistent sizes of "
                                 "simulation and builder name vectors");
}

size_t StandardTestInfo::size() const
{
    return m_simulation_name.size();
}
