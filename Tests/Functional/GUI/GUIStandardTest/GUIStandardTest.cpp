// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/GUIStandardTest.cpp
//! @brief     Implements class GUIStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIStandardTest.h"
#include "DocumentModel.h"
#include "DomainSimulationBuilder.h"
#include "GISASSimulation.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "SampleModel.h"
#include "TestUtils.h"

namespace
{
std::unique_ptr<GISASSimulation> createDomainSimulation(const GISASSimulation& origin)
{
    // initializing necessary GUI
    const std::unique_ptr<DocumentModel> documentModel(new DocumentModel);
    const std::unique_ptr<SampleModel> sampleModel(new SampleModel);
    const std::unique_ptr<InstrumentModel> instrumentModel(new InstrumentModel);
    const std::unique_ptr<MaterialModel> materialModel(new MaterialModel);
    const std::unique_ptr<MaterialSvc> materialSvc(new MaterialSvc(materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(sampleModel.get(), origin);
    guiBuilder.populateInstrumentModel(instrumentModel.get(), origin);
    guiBuilder.populateDocumentModel(documentModel.get(), origin);

    std::unique_ptr<GISASSimulation> result(DomainSimulationBuilder::getSimulation(
            sampleModel->multiLayerItem(), instrumentModel->instrumentItem(),
            documentModel->getSimulationOptionsItem()));

    return result;
}

}


bool GUIStandardTest::runTest()
{
    if (!m_reference_simulation)
        throw Exceptions::NullPointerException(
            "GUITest::runTest() -> Error. Uninitialized simulation object.");

    m_reference_simulation->runSimulation();

    auto domain_simulation = createDomainSimulation(*m_reference_simulation);
    domain_simulation->runSimulation();

    const std::unique_ptr<OutputData<double> > domain_data(
                domain_simulation->getDetectorIntensity());
    const std::unique_ptr<OutputData<double> > reference_data(
        m_reference_simulation->getDetectorIntensity());

    return TestUtils::isTheSame(*domain_data, *reference_data, m_threshold);
}
