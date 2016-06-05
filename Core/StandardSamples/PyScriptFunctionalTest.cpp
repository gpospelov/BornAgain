// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/PyScriptFunctionalTest.cpp
//! @brief     Implements class PyScriptFunctionalTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyScriptFunctionalTest.h"
#include "SimulationRegistry.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataFunctions.h"
#include "PyGenTools.h"
#include "BAPython.h"
#include "FileSystem.h"
#include "Utils.h"
#include <memory>
#include <fstream>

namespace {
const std::string temp_python_script_file_name = "PythonScript.py";
const std::string temp_intensity_data_file_name = "output.int";
const std::string directory_name_for_failed_tests = "00_failed_tests";
}

PyScriptFunctionalTest::PyScriptFunctionalTest(
    const std::string &name, const std::string &description,
    GISASSimulation *reference_simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
{
}

PyScriptFunctionalTest::~PyScriptFunctionalTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void PyScriptFunctionalTest::runTest()
{
    if (!m_reference_simulation) {
        throw NullPointerException(
            "AdvancedGUIFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }

    m_reference_simulation->runSimulation();

    runPyScriptSimulation();
}

int PyScriptFunctionalTest::analyseResults()
{
    const std::unique_ptr<OutputData<double> > P_domain_data(
        IntensityDataIOFactory::readOutputData(temp_intensity_data_file_name));

    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);

    if (getTestResult() != SUCCESS)
        savePyScript();


    return m_result;
}

void PyScriptFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
    if (getTestResult() != SUCCESS)
        ostr << "--> " << getPyScriptFileNameAndPath();
}

void PyScriptFunctionalTest::setPyScriptFileName(const std::string &file_name)
{
    m_pyscript_file_name = file_name;
}

void PyScriptFunctionalTest::runPyScriptSimulation()
{
    generatePythonScript();

    std::ofstream pythonFile;
    pythonFile.open(temp_python_script_file_name.c_str());
    pythonFile << m_pyscript_text;
    pythonFile.close();

    std::string command = std::string(BORNAGAIN_PYTHON_EXE ) + " " + temp_python_script_file_name;
    int return_code = std::system(command.c_str());
    (void)return_code;
}

void PyScriptFunctionalTest::generatePythonScript()
{
    m_pyscript_text.clear();

    std::ostringstream ostr;
    ostr << "import sys\n";
    ostr << "import os\n";
    ostr << "sys.path.append(os.path.abspath("
               << "os.path.join(os.path.split(os.path.realpath(__file__))[0],"
               << "'..', '..', '..', 'lib')))\n\n";
    ostr << PyGenTools::genPyScript(m_reference_simulation);
    m_pyscript_text = ostr.str();
}

void PyScriptFunctionalTest::savePyScript() const
{
    Utils::FileSystem::CreateDirectory(directory_name_for_failed_tests);
    std::ofstream pythonFile;
    pythonFile.open(getPyScriptFileNameAndPath().c_str());
    pythonFile << m_pyscript_text;
    pythonFile.close();
}

std::string PyScriptFunctionalTest::getPyScriptFileNameAndPath() const
{
    std::string result
        = Utils::FileSystem::GetJoinPath(directory_name_for_failed_tests, m_pyscript_file_name);
    return result;
}
