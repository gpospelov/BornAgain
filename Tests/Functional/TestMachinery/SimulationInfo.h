// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/SimulationInfo.h
//! @brief     Defines class SimulationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONINFO_H
#define SIMULATIONINFO_H

#include <string>

//! @class SimulationInfo
//! @ingroup standard_samples
//! @brief Parameter set to describe a simulation example.
//!   Used for communication from StandardSimulationsRegistry to IStandardTest.

class SimulationInfo
{
public:
    SimulationInfo();
    SimulationInfo(const std::string& test_name,
                       const std::string& test_description,
                       const std::string& simulation_name,
                       const std::string& sample_builder_name,
                       const std::string& subtest_type,
                       double threshold);

    std::string m_test_name;
    std::string m_test_description;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
    std::string m_subtest_type;
    double m_threshold;
};

#endif // SIMULATIONINFO_H
