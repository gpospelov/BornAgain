// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreStandardTest/CoreStandardTest.cpp
//! @brief     Implements class CoreStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/CoreStandardTest/CoreStandardTest.h"
#include "BABuild.h"
#include "BATesting.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Tools/FileSystemUtils.h"
#include "Tests/Functional/TestMachinery/TestUtils.h"
#include <cassert>

bool CoreStandardTest::runTest()
{
    std::unique_ptr<OutputData<double>> reference;

    // Load reference if available
    assert(m_name!="");
    try {
        reference.reset(IntensityDataIOFactory::readOutputData(
            FileSystemUtils::jointPath(BATesting::CoreReferenceDir(), m_name + ".int.gz")));
    } catch (const std::exception&) {
        std::cout << "No reference found, but we proceed with the simulation to create a new one\n";
    }

    // Run simulation.
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();
    auto sim_result = m_reference_simulation->result();
    const auto result_data = sim_result.data();

    // Compare with reference if available.
    bool success = false;
    if (reference)
        success = TestUtils::isTheSame(*result_data, *reference, m_threshold) ? true : false;

    // Save simulation if different from reference.
    if (!success) {
        FileSystemUtils::createDirectories(BATesting::CoreOutputDir());
        std::string out_fname =
            FileSystemUtils::jointPath(BATesting::CoreOutputDir(), m_name + ".int.gz");
        IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
        std::cout << "New simulation result stored in " << out_fname << "\n"
                  << "To visualize an intensity map, use " << BABuild::buildBinDir()
                  << "/plot_intensity_data.py;"
                  << "   to plot a difference image, use " << BABuild::buildBinDir()
                  << "/plot_intensity_data_diff.py\n"
                  << "If the new result is correct, then move it to "
                  << BATesting::CoreReferenceDir() << "/\n";
    }
    return success;
}
