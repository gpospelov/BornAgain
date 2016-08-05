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
    std::string output_filename = BUILD_TMP_DIR + "/" + getName() + ".int";
    std::remove( output_filename.c_str() );
    std::cout << "Removed old data set " << output_filename << "." << std::endl/*sic*/;

    // Run Python script
    std::string py_filename( m_directory + "/" + getName() + ".py" );
    std::string command =
        "PYTHONPATH=" + BUILD_LIB_DIR + " " +
        BORNAGAIN_PYTHON_EXE + " " + py_filename + " " + output_filename;
    std::cout << "Now running command '" << command << "'." << std::endl/*sic*/;
    int ret = std::system(command.c_str());
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    m_result = SUCCESS;
    return;
/*

    // Run direct simulation
    std::cout <<
        "Now going to directly run the simulation, and to compare with result from Py script.\n";
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());

    // Compare results
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(m_output_filename));
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
*/
}

void PyPersistenceTest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
}
