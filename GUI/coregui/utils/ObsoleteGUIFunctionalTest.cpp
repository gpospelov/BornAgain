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

#include "ObsoleteGUIFunctionalTest.h"
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

ObsoleteGUIFunctionalTest::ObsoleteGUIFunctionalTest(const std::string &name)
    : m_name(name), m_threshold(2e-10), m_reference_simulation(0), m_domain_simulation(0)
{
    SimulationRegistry sim_registry;
    m_reference_simulation = sim_registry.createSimulation(m_name);
}

ObsoleteGUIFunctionalTest::~ObsoleteGUIFunctionalTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void ObsoleteGUIFunctionalTest::runTest()
{
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();
}

int ObsoleteGUIFunctionalTest::analyseResults()
{
    boost::scoped_ptr<OutputData<double> > P_domain_data(m_domain_simulation->getIntensityData());
    boost::scoped_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getIntensityData());
    double diff = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);

    std::cout << m_name << " "
              << " " << diff << " " << (diff > m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if (diff > m_threshold)
        return FAILED;
    return SUCCESS;
}

//! returns new simulation from
void ObsoleteGUIFunctionalTest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());
    // initializing necessary GUI
    boost::scoped_ptr<SampleModel> P_sampleModel(new SampleModel());
    boost::scoped_ptr<InstrumentModel> P_instrumentModel(new InstrumentModel());
    boost::scoped_ptr<MaterialModel> P_materialModel(new MaterialModel());
    boost::scoped_ptr<MaterialEditor> P_materialEditor(new MaterialEditor(P_materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(P_sampleModel.get(), *m_reference_simulation);
    guiBuilder.populateInstrumentModel(P_instrumentModel.get(), *m_reference_simulation);

    m_domain_simulation
        = DomainSimulationBuilder::getSimulation(P_sampleModel.get(), P_instrumentModel.get());
}

int OBSOLETE_GUI_FUNCTIONAL_TEST(const std::string &name)
{
    ObsoleteGUIFunctionalTest test(name);
    test.runTest();
    return test.analyseResults();
}
