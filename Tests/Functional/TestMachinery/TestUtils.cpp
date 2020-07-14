// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.cpp
//! @brief     Implements TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/TestMachinery/TestUtils.h"
#include "BABuild.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Tests/Functional/TestMachinery/StandardTestCatalog.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

StandardTestInfo TestUtils::testInfo(int argc, char** argv)
{
    assert(argc > 1);
    return StandardTestCatalog().testInfo(argv[1]);
}

bool TestUtils::isTheSame(const OutputData<double>& dat, const OutputData<double>& ref,
                          double threshold)
{
    double diff = IntensityDataFunctions::getRelativeDifference(dat, ref);
    if (diff > threshold) {
        std::cerr << "  => FAILED: relative deviation of dat from ref is " << diff
                  << ", above given threshold " << threshold << "\n";
        return false;
    }
    if (diff)
        std::cerr << "  => OK: relative deviation of dat from ref is " << diff
                  << ", within given threshold " << threshold << "\n";
    else
        std::cout << "  => OK: dat = ref\n";
    return true;
}

//! Runs a python command, prints messages, returns true unless the system call failed.
bool TestUtils::runPython(const std::string& py_command)
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
