// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFunctionalTest.cpp
//! @brief     Implements class CoreFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreFunctionalTest.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"

CoreFunctionalTest::CoreFunctionalTest(const std::string &name, const std::string &description,
                                       GISASSimulation *simulation, OutputData<double> *reference,
                                       double threshold)
    : IFunctionalTest(name, description), m_simulation(simulation), m_reference(reference),
      m_threshold(threshold), m_difference(0)
{
}

CoreFunctionalTest::~CoreFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}

void CoreFunctionalTest::runTest()
{
    if(!m_simulation) {
        throw NullPointerException("AdvancedFunctionalTest::runTest() -> Error. Uninitialized simulation object.");
    }
    m_simulation->runSimulation();
}

int CoreFunctionalTest::analyseResults()
{
    if(!m_reference)  {
        m_result = FAILED_NOREF;
    } else {
        m_difference = IntensityDataFunctions::getRelativeDifference(*m_simulation->getOutputData(), *m_reference);
        m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    }
    return m_result;
}

const OutputData<double> *CoreFunctionalTest::getOutputData() const
{
    if(m_simulation) {
        return m_simulation->getOutputData();
    }
    return 0;
}

void CoreFunctionalTest::printResults(std::ostream &ostr) const
{
    ostr << getFormattedInfoString();
    if(getTestResult() == SUCCESS || getTestResult() == FAILED_DIFF)
        ostr << getDifference();
}

