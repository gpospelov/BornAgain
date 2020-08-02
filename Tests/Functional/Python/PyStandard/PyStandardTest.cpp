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
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Tools/FileSystemUtils.h"
#include <cassert>
#include <fstream>
#include <iostream>

namespace
{

} // namespace

//! Runs simulation via a Python script and directly, and returns true if the results agree.
bool PyStandardTest::runTest()
{
    // Set output data filename, and remove old output files
    assert(m_name != "");
    const std::string output_name =
        FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), m_name);
    const std::string output_path = output_name + ".ref.int.gz";
    std::remove(output_path.c_str());
    std::cout << "- removed old output " << output_path << "\n";

    // Generate Python script
    const std::string pyscript_filename =
        FileSystemUtils::jointPath(BATesting::PyStandardOutputDir(), m_name + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << ExportToPython::generatePyExportTest(*m_reference_simulation);
    pythonFile.close();

    // Run Python script
    const std::string py_command = pyscript_filename + " " + output_path;
#ifndef _WIN32
    const std::string sys_command = std::string("PYTHONPATH=") + BABuild::buildLibDir() + " "
                                    + std::string("NOPLOT=TRUE") + " " + BABuild::pythonExecutable()
                                    + " -B " + py_command;
#else
    const std::string sys_command = std::string("set PYTHONPATH=") + BABuild::buildLibDir() + " & "
                                    + std::string("set NOPLOT=TRUE") + " & \""
                                    + BABuild::pythonExecutable() + "\" -B " + py_command;
#endif
    std::cout << "- system call: " << sys_command << std::endl; // note: endl = \n + flush
    int ret = std::system(sys_command.c_str());
    if (ret != 0) {
        std::stringstream msg;
        msg << "System call returned non-zero value " << ret;
        throw std::runtime_error(msg.str());
    }

    // Run direct simulation
    std::cout << "- run reference simulation\n";
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double>> reference_data =
        m_reference_simulation->result().data();

    // Compare results
    const std::unique_ptr<OutputData<double>> domain_data(
        IntensityDataIOFactory::readOutputData(output_path));

    return IntensityDataFunctions::checkRelativeDifference(*domain_data, *reference_data,
                                                           m_threshold);
}
