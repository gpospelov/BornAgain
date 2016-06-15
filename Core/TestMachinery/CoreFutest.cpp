// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/CoreFutest.cpp
//! @brief     Implements class CoreFutest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreFutest.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "TestConfig.h"
#include "FileSystem.h"
#include "IntensityDataIOFactory.h"
#include "OutputDataIOHelper.h"
#include "Utils.h"

namespace
{
const std::string directory_name_for_failed_tests = "00_failed_tests";
}

CoreFutest::CoreFutest(
    const std::string& name, const std::string& description, GISASSimulation* simulation,
    double threshold)
    : IFutest(name, description)
    , m_simulation(simulation)
    , m_threshold(threshold)
    , m_difference(0)
{
}

CoreFutest::~CoreFutest()
{
    delete m_simulation;
    delete m_reference;
}

void CoreFutest::runTest()
{
    if (!m_simulation)
        throw NullPointerException(
            "AdvancedFutest::runTest() -> Error. Uninitialized simulation object.");
    m_simulation->runSimulation();

    m_reference = nullptr;
    std::string ref_filename = BA_REF_DATA_DIR + "/ref_" + getName() + ".int.gz";
    try {
        m_reference = IntensityDataIOFactory::readOutputData( ref_filename );
    } catch(const std::exception& ex) {
        throw std::runtime_error(
            std::string("FutestSuite::getReferenceData() -> Exception caught: ") + ex.what() );
    }
}

int CoreFutest::analyseResults()
{
    if (!m_reference) {
        m_result = FAILED_NOREF;
    } else {
        try {
            const std::unique_ptr<OutputData<double> >
                result_data(m_simulation->getDetectorIntensity());
            m_difference = IntensityDataFunctions::getRelativeDifference(
                *result_data.get(), *m_reference);
            m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
        } catch(const std::exception& ex) {
            std::cout << "CoreFutest::analyseResults() -> "
                "Intensity data comparison failed\n";
            std::cout << ex.what() << std::endl;
            m_result = FAILED_DIFF;
        }
    }

    if (getTestResult() != SUCCESS)
        saveSimulationResults();

    return m_result;
}

void CoreFutest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);

    if (getTestResult() != SUCCESS)
        ostr << "--> " << getSimulationResultsFileNameAndPath();
}

//! Saves simulation results into the file. Called if test has failed.
void CoreFutest::saveSimulationResults() const
{
    Utils::FileSystem::CreateDirectory(directory_name_for_failed_tests);
    IntensityDataIOFactory::writeOutputData(
        *(getIntensityData()), getSimulationResultsFileNameAndPath());
}

//! Constructs file name to save results. Strip gzip extention if necessary.
std::string CoreFutest::getSimulationResultsFileNameAndPath() const
{
    std::string result = Utils::FileSystem::GetJoinPath(
        directory_name_for_failed_tests, "ref_" + getName() + ".int.gz");
    return result;
}

OutputData<double>* CoreFutest::getIntensityData() const
{
    if (m_simulation)
        return m_simulation->getDetectorIntensity();
    return 0;
}
