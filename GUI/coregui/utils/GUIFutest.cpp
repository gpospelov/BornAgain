// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/GUIFutest.cpp
//! @brief     Implements class GUIFutest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIFutest.h"
#include "SimulationFactory.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "MaterialSvc.h"
#include "MaterialModel.h"
#include "Instrument.h"
#include "DomainObjectBuilder.h"
#include "SessionItem.h"
#include "IntensityDataFunctions.h"
#include "DomainSimulationBuilder.h"
#include "DocumentModel.h"
#include "Utils.h"

#include <QDebug>


GUIFutest::GUIFutest(const std::string &name, const std::string &description,
                                     GISASSimulation *reference_simulation, double threshold)
    : IFutest(name, description)
    , m_reference_simulation(reference_simulation)
    , m_domain_simulation(0)
    , m_threshold(threshold)
    , m_difference(0)
{
}

GUIFutest::~GUIFutest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}

void GUIFutest::runTest()
{
    if (!m_reference_simulation) {
        throw NullPointerException(
            "AdvancedGUIFutest::runTest() -> Error. Uninitialized simulation object.");
    }

    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();
}

int GUIFutest::analyseResults()
{
    const std::unique_ptr<OutputData<double> > P_domain_data(m_domain_simulation->getDetectorIntensity());
    const std::unique_ptr<OutputData<double> > P_reference_data(
        m_reference_simulation->getDetectorIntensity());
    m_difference = IntensityDataFunctions::getRelativeDifference(*P_domain_data, *P_reference_data);
    m_result = (m_difference > m_threshold ? FAILED_DIFF : SUCCESS);
    return m_result;
}

void GUIFutest::printResults(std::ostream &ostr) const
{
    ostr << getFormattedInfoString();
    ostr << Utils::String::getScientificDoubleString(m_difference);
}


//! returns new simulation from
void GUIFutest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());

    // initializing necessary GUI
    const std::unique_ptr<DocumentModel> documentModel(new DocumentModel());
    const std::unique_ptr<SampleModel> sampleModel(new SampleModel());
    const std::unique_ptr<InstrumentModel> instrumentModel(new InstrumentModel());
    const std::unique_ptr<MaterialModel> materialModel(new MaterialModel());
    const std::unique_ptr<MaterialSvc> materialSvc(new MaterialSvc(materialModel.get()));

    // populating GUI models from domain
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(sampleModel.get(), *m_reference_simulation);
    guiBuilder.populateInstrumentModel(instrumentModel.get(), *m_reference_simulation);
    guiBuilder.populateDocumentModel(documentModel.get(), *m_reference_simulation);

    m_domain_simulation = DomainSimulationBuilder::getSimulation(sampleModel->multiLayerItem(),
            instrumentModel->instrumentItem(), documentModel->getSimulationOptionsItem());
}
