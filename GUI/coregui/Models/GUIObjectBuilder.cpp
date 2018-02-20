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

SessionItem* GUIObjectBuilder::populateSampleModelFromSim(SampleModel* sampleModel,
                                                   MaterialModel* materialModel,
                                                   const Simulation& simulation)
{
    std::unique_ptr<Simulation> sim(simulation.clone());
    sim->prepareSimulation();
    SessionItem* item
        = populateSampleModel(sampleModel, materialModel, *sim->sample());
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

    if (const GISASSimulation* gisasSimulation
        = dynamic_cast<const GISASSimulation*>(&simulation)) {

        GISASInstrumentItem* p_instrument_item = dynamic_cast<GISASInstrumentItem*>(
            p_instrument_model->insertNewItem(Constants::GISASInstrumentType));

        if (instrument_name.isEmpty()) {
            p_instrument_item->setItemName(gisasSimulation->getInstrument().getName().c_str());
        } else {
            p_instrument_item->setItemName(instrument_name);
        }

        // beam
        auto& beam_item = p_instrument_item->item<BeamItem>(Instrument2DItem::P_BEAM);
        TransformFromDomain::setItemFromSample(&beam_item, *gisasSimulation);

        // detector
        TransformFromDomain::setInstrumentDetectorFromSample(p_instrument_item, *gisasSimulation);

        // detector masks
        TransformFromDomain::setDetectorMasks(p_instrument_item->detectorItem(), *gisasSimulation);

        // background
        TransformFromDomain::setBackground(p_instrument_item, *gisasSimulation);

        return p_instrument_item;
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
