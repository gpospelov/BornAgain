// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.cpp
//! @brief     Implements class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AdvancedFunctionalTest.h"
#include "GISASSimulation.h"
#include "IntensityDataFunctions.h"

AdvancedFunctionalTest::AdvancedFunctionalTest(const std::string &name, GISASSimulation *simulation, OutputData<double> *reference, double threshold)
    : m_name(name)
    , m_simulation(simulation)
    , m_reference(reference)
    , m_threshold(threshold)
{

}

AdvancedFunctionalTest::~AdvancedFunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}

void AdvancedFunctionalTest::runTest()
{
    assert(m_simulation);
    m_simulation->runSimulation();
}

int AdvancedFunctionalTest::analyseResults()
{
    if(!m_reference)  return FAILED;

    double diff = IntensityDataFunctions::getRelativeDifference(*m_simulation->getOutputData(),*m_reference);

    std::cout << m_name << " " << diff
              << " " << (diff>m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > m_threshold ) return FAILED;
    return SUCCESS;
}

