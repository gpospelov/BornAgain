// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/SimulationInfo.cpp
//! @brief     Implements class SimulationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardTestInfo.h"

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
    , m_simulation_name(simulation_name)
    , m_sample_builder_name(sample_builder_name)
    , m_threshold(threshold)
{
}
