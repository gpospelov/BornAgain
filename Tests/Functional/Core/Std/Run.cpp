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

#include "BABuild.h"
#include "BATesting.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/Simulation/Simulation.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/StandardSamples/SimulationFactory.h"
#include "Core/Tools/FileSystemUtils.h"
#include "Core/Multilayer/MultiLayer.h"
#include <cassert>
#include <iostream>

int run(const std::string& test_name, const std::string& sim_name, const std::string& sample_name,
        const double limit)
{
    std::cout << "run std test " << test_name << std::endl;
    std::unique_ptr<OutputData<double>> reference;

    // Load reference if available
    assert(test_name != "");
    try {
        reference.reset(IntensityDataIOFactory::readOutputData(
            FileSystemUtils::jointPath(BATesting::CoreReferenceDir(), test_name + ".int.gz")));
    } catch (const std::exception&) {
        std::cout << "No reference found, but we proceed with the simulation to create a new one\n";
    }

    std::cout << "- create sim " << sim_name << std::endl;
    std::unique_ptr<Simulation> simulation{SimulationFactory().createItem(sim_name)};
    assert(simulation);

    std::cout << "- create sam " << sample_name << std::endl;
    std::unique_ptr<MultiLayer> sample{SampleBuilderFactory().createSample(sample_name)};
    assert(sample);

    std::cout << "- set sample" << std::endl;
    simulation->setSample(*sample);

    std::cout << "- run" << std::endl;
    simulation->runSimulation();
    std::cout << "- query" << std::endl;
    auto sim_result = simulation->result();
    const auto result_data = sim_result.data();

    // Compare with reference if available.
    bool success = false;
    if (reference) {
        std::cout << "- check diff" << std::endl;
        success = IntensityDataFunctions::checkRelativeDifference(*result_data, *reference, limit);
    }

    // Save simulation if different from reference.
    if (!success) {
        std::cout << "- failure ..." << std::endl;
        FileSystemUtils::createDirectories(BATesting::CoreOutputDir());
        std::string out_fname =
            FileSystemUtils::jointPath(BATesting::CoreOutputDir(), test_name + ".int.gz");
        IntensityDataIOFactory::writeOutputData(*result_data, out_fname);
        std::cout << "New simulation result stored in " << out_fname << "\n"
                  << "To visualize an intensity map, use " << BABuild::buildBinDir()
                  << "/plot_intensity_data.py;"
                  << "   to plot a difference image, use " << BABuild::buildBinDir()
                  << "/plot_intensity_data_diff.py\n"
                  << "If the new result is correct, then move it to "
                  << BATesting::CoreReferenceDir() << "/\n";
    }
    return success ? 1 : 0;
}
