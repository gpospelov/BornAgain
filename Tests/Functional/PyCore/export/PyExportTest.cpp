// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyExportTest.cpp
//! @brief     Implements class PyExportTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyExportTest.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "PythonFormatting.h"
#include "SimulationFactory.h"
#include "Utils.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>

PyExportTest::PyExportTest(
    const std::string& name, const std::string& description,
    GISASSimulation* reference_simulation, double threshold)
    : IReferencedTest(name, description, threshold)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(nullptr)
{
}

PyExportTest::~PyExportTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void PyExportTest::runTest()
{
    // Generate Python script
    std::string pyscript_filename = Utils::FileSystem::GetJoinPath(PYEXPORT_TMP_DIR,
                                                                   getName() + ".py");
    std::ostringstream ostr;
    ostr << PythonFormatting::simulationToPython(m_reference_simulation);
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << ostr.str();
    pythonFile.close();
    std::cout << "Generated Python script " << pyscript_filename <<"." << std::endl/*sic*/;
        // Here we are using std::endl instead of "\n" in order to flush because otherwise
        // the system calls 'remove' and 'system' may break the order of output lines.

    // Run Python script
    std::string output_name = Utils::FileSystem::GetJoinPath(PYEXPORT_TMP_DIR, getName());
    std::string output_path = output_name + ".ref.int";
    std::remove( output_path.c_str() );
    std::cout << "Removed old data set " << output_path << "." << std::endl/*sic*/;
    assert(std::string(BUILD_LIB_DIR)!="");
    std::string command =
        std::string("PYTHONPATH=") + BUILD_LIB_DIR + " " +
        BORNAGAIN_PYTHON_EXE + " " + pyscript_filename + " " + output_name;
    std::cout << "Now running command '" << command << "'." << std::endl/*sic*/;
    int ret = std::system(command.c_str()); // run python script
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << ".\n";
        m_result = FAILED;
        return;
    }

    // Run direct simulation
    std::cout <<
        "Now going to directly run the simulation, and to compare with result from Py script.\n";
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());

    // Compare results
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(output_path));
    m_result = compareIntensityMaps(*P_domain_data, *P_reference_data);
}
