// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.cpp
//! @brief     Implements class IFunctionalTest.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFunctionalTest.h"
#include "SimulationRegistry.h"
#include "OutputDataIOFactory.h"
#include "OutputDataFunctions.h"
#include "FileSystem.h"


FunctionalTest::FunctionalTest(const FunctionalTestInfo &info)
    : m_info(info),
      m_simulation(0),
      m_reference(0)
{
    SimulationRegistry sim_registry;
    m_simulation = sim_registry.createSimulation(getName());

    std::string filename = Utils::FileSystem::GetReferenceDataDir() + m_info.m_reference_file;
    m_reference = OutputDataIOFactory::readIntensityData(filename);
}


FunctionalTest::~FunctionalTest()
{
    delete m_simulation;
    delete m_reference;
}


void FunctionalTest::runTest()
{
    m_simulation->runSimulation();
}


int FunctionalTest::analyseResults()
{
    assert(m_simulation);
//    assert(m_result);
    assert(m_reference);
    double diff = OutputDataFunctions::GetDifference(*getResult(),*m_reference);

    std::cout << getName() << " " << getDescription() << " " << diff
              << " " << (diff>m_info.m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > m_info.m_threshold ) return FAILED;
    return SUCCESS;
}
