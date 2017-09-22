// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.cpp
//! @brief     Implements pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "IntensityDataFunctions.h"
#include <iostream>
#include <cstdlib>

#ifdef PYTHON_EXECUTABLE
//! Runs a python command, prints messages, returns true unless the system call failed.
bool IStandardTest::runPython(const std::string& py_command)
{
#ifndef _WIN32
    std::string sys_command = std::string("PYTHONPATH=") + BUILD_LIB_DIR + " " +
        PYTHON_EXECUTABLE + " -B " + py_command;
#else
    std::string sys_command = std::string("set PYTHONPATH=") + BUILD_LIB_DIR + " & " +
        PYTHON_EXECUTABLE + " -B " + py_command;
#endif
    std::cout << sys_command << std::endl/*sic*/; // flush output before calling std::system
    int ret = std::system(sys_command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << "\n";
        return false;
    }
    return true;
}
#endif
