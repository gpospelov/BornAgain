// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FutestInfo.cpp
//! @brief     Implements class FutestInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FutestInfo.h"

FutestInfo::FutestInfo()
    : m_threshold(0.0)
{
}

FutestInfo::FutestInfo(const std::string &test_name,
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

