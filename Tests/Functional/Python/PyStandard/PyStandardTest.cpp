// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyStandard/PyStandardTest.cpp
//! @brief     Implements class PyExportTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Python/PyStandard/PyStandardTest.h"
#include "BABuild.h"
#include "BATesting.h"
#include "Core/Export/ExportToPython.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Tools/FileSystemUtils.h"
#include "Tests/Functional/TestMachinery/TestUtils.h"
#include <cassert>
#include <fstream>
#include <iostream>

namespace {

//! Runs a python command, prints messages, returns true unless the system call failed.
bool runPython(const std::string& py_command)
{
#ifndef _WIN32
    std::string sys_command = std::string("PYTHONPATH=") + BABuild::buildLibDir() + " "
                              + std::string("NOPLOT=TRUE") + " " + BABuild::pythonExecutable()
                              + " -B " + py_command;
#else
    std::string sys_command = std::string("set PYTHONPATH=") + BABuild::buildLibDir() + " & "
                              + std::string("set NOPLOT=TRUE") + " & \""
                              + BABuild::pythonExecutable() + "\" -B " + py_command;
#endif
    std::cout << sys_command << std::endl /*sic*/; // flush output before calling std::system
    int ret = std::system(sys_command.c_str());
    if (ret != 0) {
        std::cerr << "Command returned non-zero value " << ret << "\n";
        return false;
    }
    return true;
}

} // namespace

//! Runs simulation via a Python script and directly, and returns true if the results agree.
bool PyStandardTest::runTest()
{
    // Set output data filename, and remove old output files
    assert(m_name != "");
    std::string output_name = FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), m_name);
    std::string output_path = output_name + ".ref.int.gz";
    std::remove(output_path.c_str());
    std::cout << "Removed old output " << output_path << "\n";

    // Generate Python script
    std::string pyscript_filename =
        FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), m_name + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << ExportToPython::generatePyExportTest(*m_reference_simulation);
    pythonFile.close();

    // Run Python script
    if (!runPython(pyscript_filename + " " + output_path))
        return false;

    // Run direct simulation
    std::cout << "Running simulation and comparing with result from Py script\n";
    m_reference_simulation->runSimulation();
    auto ref_result = m_reference_simulation->result();

    const auto reference_data = ref_result.data();

    // Compare results
    const std::unique_ptr<OutputData<double>> domain_data(
        IntensityDataIOFactory::readOutputData(output_path));

    return TestUtils::isTheSame(*domain_data, *reference_data, m_threshold);
}
