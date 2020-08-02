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
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/Simulation/Simulation.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/SampleModel.h"

namespace
{

std::unique_ptr<OutputData<double>> domainData(const std::string& /*test_name*/,
                                               const Simulation& direct_simulation)
{
    // initializing necessary GUI
    DocumentModel documentModel;
    SampleModel sampleModel;
    InstrumentModel instrumentModel;
    MaterialModel materialModel;

    // populating GUI models from domain
    GUIObjectBuilder::populateSampleModelFromSim(&sampleModel, &materialModel, direct_simulation);
    GUIObjectBuilder::populateInstrumentModel(&instrumentModel, direct_simulation);
    GUIObjectBuilder::populateDocumentModel(&documentModel, direct_simulation);

    std::unique_ptr<Simulation> domain_simulation = DomainSimulationBuilder::createSimulation(
        sampleModel.multiLayerItem(), instrumentModel.instrumentItem(),
        documentModel.simulationOptionsItem());

    domain_simulation->runSimulation();
    return std::unique_ptr<OutputData<double>>(domain_simulation->result().data());
}

} // namespace

bool GUIStandardTest::runTest()
{
    m_reference_simulation->runSimulation();
    const std::unique_ptr<OutputData<double>> ref_data = m_reference_simulation->result().data();

    const std::unique_ptr<OutputData<double>> domain_data =
        domainData(m_name, *m_reference_simulation);

    return IntensityDataFunctions::checkRelativeDifference(*domain_data, *ref_data, m_threshold);
}
