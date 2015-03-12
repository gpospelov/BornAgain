// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFunctionalTest.cpp
//! @brief     Implements class GUIFunctionalTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIFunctionalTest.h"
#include "SimulationRegistry.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "Instrument.h"
#include "DomainObjectBuilder.h"
#include "ParameterizedItem.h"
#include "IntensityDataFunctions.h"
#include "DomainSimulationBuilder.h"
#include <boost/scoped_ptr.hpp>
#include <QDebug>

GUIFunctionalTest::GUIFunctionalTest(const std::string &name)
    : m_name(name), m_threshold(2e-10), m_reference_simulation(0), m_domain_simulation(0)
{
    SimulationRegistry sim_registry;
    m_reference_simulation = sim_registry.createSimulation(m_name);
}

GUIFunctionalTest::~GUIFunctionalTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void GUIFunctionalTest::runTest()
{
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();
}

int GUIFunctionalTest::analyseResults()
{
    boost::scoped_ptr<OutputData<double> > domain_data(m_domain_simulation->getIntensityData());
    boost::scoped_ptr<OutputData<double> > reference_data(
        m_reference_simulation->getIntensityData());
    double diff = IntensityDataFunctions::getRelativeDifference(*domain_data, *reference_data);

    std::cout << m_name << " "
              << " " << diff << " " << (diff > m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if (diff > m_threshold)
        return FAILED;
    return SUCCESS;
}

//! returns new simulation from
void GUIFunctionalTest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());
    // initializing necessary GUI
    boost::scoped_ptr<SampleModel> sampleModel(new SampleModel());
    boost::scoped_ptr<InstrumentModel> instrumentModel(new InstrumentModel());
    boost::scoped_ptr<MaterialModel> materialModel(new MaterialModel());
    boost::scoped_ptr<MaterialEditor> materialEditor(new MaterialEditor(materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(sampleModel.get(), *m_reference_simulation);
    guiBuilder.populateInstrumentModel(instrumentModel.get(), *m_reference_simulation);

    m_domain_simulation
        = DomainSimulationBuilder::getSimulation(sampleModel.get(), instrumentModel.get());
}

int GUI_FUNCTIONAL_TEST(const std::string &name)
{
    GUIFunctionalTest test(name);
    test.runTest();
    return test.analyseResults();
}
