//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyStd/Check.cpp
//! @brief     Implements function checkSimulation for Python standard test
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "BABuild.h"
#include "BATesting.h"
#include "Base/Utils/FileSystemUtils.h"
#include "Core/Export/ExportToPython.h"
#include "Core/Simulation/ISimulation.h"
#include "Device/Data/DataUtils.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include <fstream>
#include <iostream>

namespace {

std::unique_ptr<OutputData<double>> domainData(const std::string& test_name,
                                               const ISimulation& direct_simulation) {
    const std::string output_name =
        FileSystemUtils::jointPath(BATesting::TestOutDir_PyStd(), test_name);
    const std::string output_path = output_name + ".ref.int.gz";
    std::remove(output_path.c_str());
    std::cout << "- removed old output " << output_path << std::endl;

    // Generate Python script
    const std::string pyscript =
        FileSystemUtils::jointPath(BATesting::TestOutDir_PyStd(), test_name + ".py");
    std::ofstream f(pyscript);
    f << ExportToPython::simulationSaveCode(direct_simulation, output_path);
    f.close();
    std::cout << "- wrote Python script " << pyscript << std::endl;

    // Run Python script
#ifndef _WIN32
    const std::string sys_command = std::string("PYTHONPATH=") + BABuild::buildLibDir() + " "
                                    + std::string("NOSHOW=TRUE") + " " + BABuild::pythonExecutable()
                                    + " -B " + pyscript;
#else
    const std::string sys_command = std::string("set PYTHONPATH=") + BABuild::buildLibDir() + " & "
                                    + std::string("set NOSHOW=TRUE") + " & \""
                                    + BABuild::pythonExecutable() + "\" -B " + pyscript;
#endif
    std::cout << "- system call: " << sys_command << std::endl;
    int err = std::system(sys_command.c_str());
    std::cout << "- system call returned " << err << std::endl;
    if (err)
        throw std::runtime_error("Exported Python script did not execute properly");

    auto ret =
        std::unique_ptr<OutputData<double>>(IntensityDataIOFactory::readOutputData(output_path));
    if (!ret)
        throw std::runtime_error("Could not read back simulation output from file " + output_path);
    return ret;
}

} // namespace

//! Run simulation directly (in C+ core) and through Python export, and compare results.

bool checkSimulation(const std::string& name, const ISimulation& direct_simulation,
                     const double limit) {
    std::cout << "PyStd test: checkSimulation(" << name << ")" << std::endl;

    const std::unique_ptr<OutputData<double>> domain_data = domainData(name, direct_simulation);
    std::cout << "- got domain data" << std::endl;
    const std::unique_ptr<OutputData<double>> ref_data = direct_simulation.result().data();
    std::cout << "- ran simulation" << std::endl;

    return DataUtils::checkRelativeDifference(*domain_data, *ref_data, limit);
}
