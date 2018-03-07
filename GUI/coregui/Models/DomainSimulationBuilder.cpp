// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainSimulationBuilder.cpp
//! @brief     Implements class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DomainSimulationBuilder.h"
#include "AxesItems.h"
#include "BackgroundItems.h"
#include "BeamItems.h"
#include "DetectorItems.h"
#include "DomainObjectBuilder.h"
#include "FootprintItems.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IBackground.h"
#include "IFootprintFactor.h"
#include "InstrumentItems.h"
#include "MultiLayer.h"
#include "MultiLayerItem.h"
#include "OffSpecSimulation.h"
#include "SimulationOptionsItem.h"
#include "SpecularSimulation.h"
#include "SpecularBeamInclinationItem.h"
#include "TransformToDomain.h"
#include "Units.h"

namespace {
void addBackgroundToSimulation(const InstrumentItem& instrument, Simulation& simulation);

std::unique_ptr<GISASSimulation> createGISASSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                       const GISASInstrumentItem* gisasInstrument,
                                                       const SimulationOptionsItem* optionsItem);

std::unique_ptr<OffSpecSimulation>
createOffSpecSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                        const OffSpecInstrumentItem* offspecInstrument,
                        const SimulationOptionsItem* optionsItem);

std::unique_ptr<SpecularSimulation>
createSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                         const SpecularInstrumentItem* specular_instrument,
                         const SimulationOptionsItem* options_item);
}

std::unique_ptr<Simulation>
DomainSimulationBuilder::createSimulation(const MultiLayerItem* sampleItem,
                                          const InstrumentItem* instrumentItem,
                                          const SimulationOptionsItem* optionsItem)
{
    if (sampleItem == nullptr || instrumentItem == nullptr) {
        QString message("DomainSimulationBuilder::getSimulation() -> Error. Either MultiLayerItem "
                        " or InstrumentItem is not defined.");
        throw GUIHelpers::Error(message);
    }

    auto P_multilayer = DomainObjectBuilder::buildMultiLayer(*sampleItem);

    if (auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(instrumentItem))
        return createGISASSimulation(std::move(P_multilayer), gisasInstrument, optionsItem);
    else if (auto offspecInstrument = dynamic_cast<const OffSpecInstrumentItem*>(instrumentItem))
        return createOffSpecSimulation(std::move(P_multilayer), offspecInstrument, optionsItem);
    else if (auto specular_instrument = dynamic_cast<const SpecularInstrumentItem*>(instrumentItem))
        return createSpecularSimulation(std::move(P_multilayer), specular_instrument, optionsItem);

    throw GUIHelpers::Error(
        "DomainSimulationBuilder::createSimulation() -> Error. Not yet implemented");
}

namespace
{
void addBackgroundToSimulation(const InstrumentItem& instrument, Simulation& simulation)
{
    auto P_background = instrument.backgroundItem()->createBackground();
    if (P_background)
        simulation.setBackground(*P_background);
}

std::unique_ptr<GISASSimulation> createGISASSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                  const GISASInstrumentItem* gisasInstrument,
                                                  const SimulationOptionsItem* optionsItem)
{
    std::unique_ptr<GISASSimulation> gisas(new GISASSimulation);
    auto P_instrument = DomainObjectBuilder::buildInstrument(*gisasInstrument);
    gisas->setSample(*P_multilayer);
    gisas->setInstrument(*P_instrument);
    TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(),
                                                             *gisas.get());

    // Simulation options
    if (optionsItem)
        TransformToDomain::setSimulationOptions(gisas.get(), *optionsItem);

    addBackgroundToSimulation(*gisasInstrument, *gisas);

    return gisas;
}

std::unique_ptr<OffSpecSimulation> createOffSpecSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                    const OffSpecInstrumentItem* offspecInstrument,
                                                    const SimulationOptionsItem* optionsItem)
{
    std::unique_ptr<OffSpecSimulation> offspec(new OffSpecSimulation);
    auto P_instrument = DomainObjectBuilder::buildInstrument(*offspecInstrument);
    offspec->setSample(*P_multilayer);
    offspec->setInstrument(*P_instrument);

    auto beamItem = offspecInstrument->beamItem();
    auto axisItem = dynamic_cast<BasicAxisItem*>(
        offspecInstrument->getItem(OffSpecInstrumentItem::P_ALPHA_AXIS));
    offspec->setBeamParameters(beamItem->getWavelength(), *axisItem->createAxis(Units::degree),
                               beamItem->getAzimuthalAngle());

    // TODO Take care about distributions
    // TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(),
    //                                                          gisas.get());

    // Simulation options
    if (optionsItem)
        TransformToDomain::setSimulationOptions(offspec.get(), *optionsItem);

    addBackgroundToSimulation(*offspecInstrument, *offspec);

    return offspec;
}

std::unique_ptr<SpecularSimulation>
createSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                         const SpecularInstrumentItem* specular_instrument,
                         const SimulationOptionsItem* options_item)
{
    std::unique_ptr<SpecularSimulation> specular_simulation
        = std::make_unique<SpecularSimulation>(*P_multilayer);

    auto beam_item = specular_instrument->beamItem();
    const auto axis_item
        = dynamic_cast<BasicAxisItem*>(beam_item->getItem(SpecularBeamItem::P_INCLINATION_ANGLE)
                                           ->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS));
    const auto footprint = beam_item->currentFootprintItem();

    specular_simulation->setBeamIntensity(beam_item->getIntensity());
    specular_simulation->setBeamParameters(beam_item->getWavelength(),
                                           *axis_item->createAxis(Units::degree),
                                           footprint->createFootprint().get());

    TransformToDomain::addDistributionParametersToSimulation(*beam_item,
                                                             *specular_simulation.get());

    // Simulation options
    if (options_item)
        TransformToDomain::setSimulationOptions(specular_simulation.get(), *options_item);

    addBackgroundToSimulation(*specular_instrument, *specular_simulation);

    return specular_simulation;
}
}
