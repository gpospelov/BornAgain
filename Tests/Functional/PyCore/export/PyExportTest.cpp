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
    // Set output data filename, and remove old output files
    std::string output_name = FileSystem::GetJoinPath(PYEXPORT_TMP_DIR, getName());
    std::string output_path = output_name + ".ref.int";
    std::remove( output_path.c_str() );
    std::cout << "Removed old output " << output_path << "n";

    // Generate Python script
    std::string pyscript_filename = FileSystem::GetJoinPath(PYEXPORT_TMP_DIR, getName() + ".py");
    std::ofstream pythonFile(pyscript_filename);
    pythonFile << PythonFormatting::simulationToPython(m_reference_simulation);
    pythonFile.close();

    // Run Python script
    assert(std::string(BUILD_LIB_DIR)!="");
    std::string command = std::string("PYTHONPATH=") + BUILD_LIB_DIR + " " +
        BORNAGAIN_PYTHON_EXE + " " + pyscript_filename + " " + output_name;
    std::cout << command << std::endl/*sic*/; // flush output before calling std::system
    int ret = std::system(command.c_str()); // run python script
    if (ret!=0) {
        std::cerr << "Command returned non-zero value " << ret << "\n";
        m_result = FAILED;
        return;
    }

    // Run direct simulation
    std::cout <<
        "Now going to directly run the simulation, and to compare with result from Py script\n";
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());

    // Compare results
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(output_path));
    m_result = compareIntensityMaps(*P_domain_data, *P_reference_data);
}
