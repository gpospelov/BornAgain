// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTest.cpp
//! @brief     Implements class SelfConsistenceTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTest.h"
#include "BATesting.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Tools/FileSystemUtils.h"
#include <cassert>

namespace
{
std::string composeName(std::string d_name, std::string test_name, size_t index)
{
    std::stringstream ss;
    ss << index;
    return FileSystemUtils::jointPath(d_name, test_name + ss.str() + ".int.gz");
}
} // namespace

SelfConsistenceTest::SelfConsistenceTest(const std::string& name,
                                         std::vector<std::unique_ptr<Simulation>> simulations,
                                         double threshold)
    : m_name(name), m_simulations(std::move(simulations)), m_threshold(threshold)
{
    assert(m_simulations.size() >= 2); // need at least two simulations to compare
}

bool SelfConsistenceTest::runTest()
{
    // Run simulation.
    std::vector<std::unique_ptr<OutputData<double>>> results;
    for (auto& simulation : m_simulations) {
        simulation->runSimulation();
        auto sim_result = simulation->result();
        results.push_back(sim_result.data());
    }

    // Compare with reference if available.
    bool success = true;
    for (size_t i = 1, size = results.size(); i < size; ++i) {
        const bool outcome =
            IntensityDataFunctions::checkRelativeDifference(*results[i], *results[0], m_threshold);
        if (!outcome) { // compose message and save results
            std::stringstream ss;
            ss << "Simulations 0 and " << i << " yield different results.\n"
               << "Results are stored in\n";
            const std::string output_dname = BATesting::SelfConsistenceOutputDir();
            FileSystemUtils::createDirectories(output_dname);
            for (size_t index : {size_t(0), i}) {
                const std::string fname = composeName(output_dname, m_name, index);
                IntensityDataIOFactory::writeOutputData(*results[index], fname);
                ss << "- " << fname << "\n";
            }
            std::cout << ss.str();
        }
        success = success && outcome;
    }

    return success;
}
