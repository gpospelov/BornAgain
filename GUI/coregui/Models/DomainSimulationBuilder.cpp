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
#include "BackgroundItems.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "DomainObjectBuilder.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IBackground.h"
#include "InstrumentItems.h"
#include "MultiLayer.h"
#include "MultiLayerItem.h"
#include "SimulationOptionsItem.h"
#include "TransformToDomain.h"

//! Creates domain simulation from sample and instrument items.
std::unique_ptr<GISASSimulation> DomainSimulationBuilder::createSimulation(const MultiLayerItem* sampleItem,
                                                        const InstrumentItem* instrumentItem,
                                                        const SimulationOptionsItem* optionsItem)
{
    if (sampleItem == nullptr || instrumentItem == nullptr) {
        QString message("DomainSimulationBuilder::getSimulation() -> Error. Either MultiLayerItem "
                        " or InstrumentItem is not defined.");
        throw GUIHelpers::Error(message);
    }
    DomainObjectBuilder builder;

    if (auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(instrumentItem)) {
        std::unique_ptr<GISASSimulation> result(new GISASSimulation);
        auto P_multilayer = builder.buildMultiLayer(*sampleItem);
        auto P_instrument = builder.buildInstrument(*gisasInstrument);
        result->setSample(*P_multilayer);
        result->setInstrument(*P_instrument);
        TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(), result.get());

        // Simulation options
        if (optionsItem)
            TransformToDomain::setSimulationOptions(result.get(), *optionsItem);

        // Background simulation
        auto P_background = gisasInstrument->backgroundItem()->createBackground();
        if (P_background)
            result->setBackground(*P_background);

        return result;

    }

    throw GUIHelpers::Error("DomainSimulationBuilder::createSimulation() -> Error. Not yet implemented");
}
