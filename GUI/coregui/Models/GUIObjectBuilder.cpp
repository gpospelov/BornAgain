// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.cpp
//! @brief     Implements GUIObjectBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUIObjectBuilder.h"
#include "BeamItem.h"
#include "DocumentModel.h"
#include "GISASSimulation.h"
#include "GUIDomainSampleVisitor.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "InstrumentModel.h"
#include "MultiLayer.h"
#include "SampleModel.h"
#include "Simulation.h"
#include "SimulationOptionsItem.h"
#include "TransformFromDomain.h"
#include "OffSpecSimulation.h"

namespace
{
GISASInstrumentItem* createGISASInstrumentItem(InstrumentModel* model,
                                               const GISASSimulation& simulation,
                                               const QString& name);

OffSpecInstrumentItem* createOffSpecInstrumentItem(InstrumentModel* model,
                                               const OffSpecSimulation& simulation,
                                               const QString& name);

}

SessionItem* GUIObjectBuilder::populateSampleModelFromSim(SampleModel* sampleModel,
                                                          MaterialModel* materialModel,
                                                          const Simulation& simulation)
{
    std::unique_ptr<Simulation> sim(simulation.clone());
    sim->prepareSimulation();
    SessionItem* item = populateSampleModel(sampleModel, materialModel, *sim->sample());
    return item;
}

SessionItem* GUIObjectBuilder::populateSampleModel(SampleModel* sampleModel,
                                                   MaterialModel* materialModel,
                                                   const MultiLayer& sample,
                                                   const QString& sample_name)
{
    GUIDomainSampleVisitor visitor;
    return visitor.populateSampleModel(sampleModel, materialModel, sample, sample_name);
}

SessionItem* GUIObjectBuilder::populateInstrumentModel(InstrumentModel* p_instrument_model,
                                                       const Simulation& simulation,
                                                       const QString& instrument_name)
{
    Q_ASSERT(p_instrument_model);

    QString name = instrument_name.isEmpty()
                       ? QString::fromStdString(simulation.getInstrument().getName())
                       : instrument_name;

    if (auto gisasSimulation = dynamic_cast<const GISASSimulation*>(&simulation)) {
        return createGISASInstrumentItem(p_instrument_model, *gisasSimulation, name);
    }

    else if(auto offSpecSimulation = dynamic_cast<const OffSpecSimulation*>(&simulation)) {
        return createOffSpecInstrumentItem(p_instrument_model, *offSpecSimulation, name);
    }

    throw GUIHelpers::Error("GUIObjectBuilder::populateInstrumentModel() -> Error. Simulation is "
                            "not yet supported");
}

SessionItem* GUIObjectBuilder::populateDocumentModel(DocumentModel* p_document_model,
                                                     const Simulation& simulation)
{
    SimulationOptionsItem* p_options_item = dynamic_cast<SimulationOptionsItem*>(
        p_document_model->insertNewItem(Constants::SimulationOptionsType));
    Q_ASSERT(p_options_item);
    if (simulation.getOptions().isIntegrate()) {
        p_options_item->setComputationMethod(Constants::SIMULATION_MONTECARLO);
        p_options_item->setNumberOfMonteCarloPoints(
            static_cast<int>(simulation.getOptions().getMcPoints()));
    }
    if (simulation.getOptions().useAvgMaterials()) {
        p_options_item->setFresnelMaterialMethod(Constants::AVERAGE_LAYER_MATERIAL);
    }
    if (simulation.getOptions().includeSpecular()) {
        p_options_item->setIncludeSpecularPeak(Constants::Yes);
    }
    return p_options_item;
}

namespace
{
GISASInstrumentItem* createGISASInstrumentItem(InstrumentModel* model,
                                               const GISASSimulation& simulation,
                                               const QString& name)
{
    auto result
        = dynamic_cast<GISASInstrumentItem*>(model->insertNewItem(Constants::GISASInstrumentType));

    result->setItemName(name);
    TransformFromDomain::setGISASBeamItem(result->beamItem(), simulation);
    TransformFromDomain::setDetector(result, simulation);
    TransformFromDomain::setBackground(result, simulation);

    return result;
}

OffSpecInstrumentItem* createOffSpecInstrumentItem(InstrumentModel* model,
                                               const OffSpecSimulation& simulation,
                                               const QString& name)
{
    auto result = dynamic_cast<OffSpecInstrumentItem*>(model->insertNewItem(Constants::OffSpecInstrumentType));

    result->setItemName(name);
    TransformFromDomain::setOffSpecBeamItem(result->beamItem(), simulation);
    TransformFromDomain::setDetector(result, simulation);
    TransformFromDomain::setBackground(result, simulation);

    return result;
}

}
