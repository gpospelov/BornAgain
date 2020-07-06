// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/GUIStandardTest.cpp
//! @brief     Implements class GUIStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/GUIStandardTest/GUIStandardTest.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "Core/Simulation/Simulation.h"
#include "Tests/Functional/TestMachinery/TestUtils.h"

namespace
{
std::unique_ptr<Simulation> createDomainSimulation(const Simulation& origin)
{
    // initializing necessary GUI
    DocumentModel documentModel;
    SampleModel sampleModel;
    InstrumentModel instrumentModel;
    MaterialModel materialModel;

    // populating GUI models from domain
    GUIObjectBuilder::populateSampleModelFromSim(&sampleModel, &materialModel, origin);
    GUIObjectBuilder::populateInstrumentModel(&instrumentModel, origin);
    GUIObjectBuilder::populateDocumentModel(&documentModel, origin);

    auto result = DomainSimulationBuilder::createSimulation(sampleModel.multiLayerItem(),
                                                            instrumentModel.instrumentItem(),
                                                            documentModel.simulationOptionsItem());

    return result;
}
} // namespace

bool GUIStandardTest::runTest()
{
    m_reference_simulation->runSimulation();
    const SimulationResult& ref_result = m_reference_simulation->result();

    std::unique_ptr<Simulation> domain_simulation = createDomainSimulation(*m_reference_simulation);
    domain_simulation->runSimulation();
    const SimulationResult& domain_result = domain_simulation->result();

    return TestUtils::isTheSame(*domain_result.data(), *ref_result.data(), m_threshold);
}
