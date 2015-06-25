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
#include <boost/scoped_ptr.hpp>
#include <fstream>

PyScriptFunctionalTest::PyScriptFunctionalTest(const std::string &name, const std::string &description,
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
    boost::scoped_ptr<OutputData<double> > P_domain_data(IntensityDataIOFactory::readIntensityData("output.int"));

    boost::scoped_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getIntensityData());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    return m_result;
}

void PyScriptFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr << getFormattedInfoString();
    ostr << getDifference();
}

void PyScriptFunctionalTest::runPyScriptSimulation()
{
    std::ofstream pythonFile;
    pythonFile.open("PythonScript.py");
    pythonFile << "import sys\n";
    pythonFile << "import os\n";
    pythonFile << "sys.path.append(os.path.abspath("
               << "os.path.join(os.path.split(os.path.realpath(__file__))[0],"
               << "'..', '..', '..', 'lib')))\n\n";
    pythonFile << PyGenTools::genPyScript(m_reference_simulation);
    pythonFile.close();

    std::string command = std::string(BORNAGAIN_PYTHON_EXE ) + " PythonScript.py";
    int return_code = std::system(command.c_str());
    (void)return_code;
//    if (std::remove("PythonScript.py") != 0) {
//        throw RuntimeErrorException("PyGenTools::testPyScript: "
//            "PythonScript.py could not be removed from filesystem");
//    }
}


