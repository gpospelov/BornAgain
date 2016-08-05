// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreTest.cpp
//! @brief     Implements class CoreTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreTest.h"
#include "FileSystem.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "TestConfig.h"
#include "Utils.h"

CoreTest::CoreTest(
    const std::string& name, const std::string& description, GISASSimulation* simulation,
    double threshold)
    : IFunctionalTest(name, description)
    , m_simulation(simulation)
    , m_threshold(threshold)
    , m_difference(0)
{
}

CoreTest::~CoreTest()
{
    delete m_simulation;
    delete m_reference;
}

void CoreTest::runTest()
{
    if (!m_simulation)
        throw Exceptions::NullPointerException(
            "CoreTest::runTest() -> Error. Uninitialized simulation object.");
    m_simulation->runSimulation();

    m_ref_filename = REFERENCE_DIR + "/StandardSuite/ref_" + getName() + ".int.gz";
    try {
        m_reference = IntensityDataIOFactory::readOutputData( m_ref_filename );
    } catch(const std::exception& ex) {
        m_reference = nullptr;
        std::cout << "proceed without reference after catching error [" << ex.what() << "]\n";
    }
    // Run simulation.
    const std::unique_ptr<OutputData<double>>
        result_data(m_simulation->getDetectorIntensity());
    // Compare with reference if available.
    if (!m_reference) {
        m_result = FAILED_NOREF;
    } else {
        m_difference = IntensityDataFunctions::getRelativeDifference(
            *result_data.get(), *m_reference);
        m_result = m_difference > m_threshold ? FAILED_DIFF : SUCCESS;
    }
    // Save simulation if different from reference.
    if (getTestResult() != SUCCESS) {
        Utils::FileSystem::CreateDirectory(FAILED_TESTS_DIR);
        IntensityDataIOFactory::writeOutputData(
            *(getIntensityData()), getSimulationResultsFileNameAndPath());
    }
}

void CoreTest::printResults(std::ostream& ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);

    if (getTestResult() != SUCCESS) {
        ostr << "\n"
             << "--> simulation result stored in " << getSimulationResultsFileNameAndPath() << "\n";
        if (m_reference) {
            ostr << "    differs from reference data " << m_ref_filename << "\n"
                 << "    (to inspect such images, use " << BUILD_BIN_DIR << "/view1.py;"
                 << " for a difference image, " << BUILD_BIN_DIR << "/view2.py)\n";
        } else {
            ostr << "    (to inspect the image, use " << BUILD_BIN_DIR << "/view1.py)\n"
                 << "    reference should have been in " << m_ref_filename << "\n";
        }
    }
}

//! Constructs file name to save results. Strip gzip extention if necessary.
std::string CoreTest::getSimulationResultsFileNameAndPath() const
{
    std::string result = Utils::FileSystem::GetJoinPath(
        FAILED_TESTS_DIR, "ref_" + getName() + ".int.gz");
    return result;
}

OutputData<double>* CoreTest::getIntensityData() const
{
    if (m_simulation)
        return m_simulation->getDetectorIntensity();
    return nullptr;
}
