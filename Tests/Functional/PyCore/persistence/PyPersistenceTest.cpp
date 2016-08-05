// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyPersistenceTest.cpp
//! @brief     Implements class PyPersistenceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyPersistenceTest.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "TestConfig.h"
#include "Utils.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

PyPersistenceTest::PyPersistenceTest(
    const std::string& directory, const std::string& name)
    : IFunctionalTest(name, "persistence test on script "+name)
    , m_directory(directory)
    , m_threshold(2e-10)
    , m_difference(0)
{}

void PyPersistenceTest::runTest()
{
    // Prepare output file
    std::string output_name = BUILD_TMP_DIR + "/" + getName();
    std::string output_path = output_name + ".int";
    std::remove( output_path.c_str() );
    std::cout << "Removed old data set " << output_path << "." << std::endl/*sic*/;

    // Run Python script
    std::string py_filename( m_directory + "/" + getName() + ".py" );
    std::string command =
        "PYTHONPATH=" + BUILD_LIB_DIR + " " +
        BORNAGAIN_PYTHON_EXE + " " + py_filename + " " + output_name;
    std::cout << "Now running command '" << command << "'." << std::endl/*sic*/;
    int ret = std::system(command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    // Read back simulation result
    const OutputData<double>* data = IntensityDataIOFactory::readOutputData( output_path );

    // Read reference data
    std::string ref_filename = REFERENCE_DIR + "/Persistence/" + getName() + ".int.gz";
    const OutputData<double>* reference;
    try {
        reference = IntensityDataIOFactory::readOutputData( ref_filename );
    } catch(const std::exception& ex) {
        std::cerr << "Cannot read reference file " << ref_filename << "\n";
        m_result = FAILED;
        return;
    }

    // Compare data
    m_difference = IntensityDataFunctions::getRelativeDifference(*data, *reference);
    m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
    return;
}

void PyPersistenceTest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
}
