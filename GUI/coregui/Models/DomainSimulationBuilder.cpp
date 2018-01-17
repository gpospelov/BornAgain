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
#include "OffSpecSimulation.h"
#include "TransformToDomain.h"

//! Creates domain simulation from sample and instrument items.
std::unique_ptr<Simulation> DomainSimulationBuilder::createSimulation(const MultiLayerItem* sampleItem,
                                                        const InstrumentItem* instrumentItem,
                                                        const SimulationOptionsItem* optionsItem)
{
    if (sampleItem == nullptr || instrumentItem == nullptr) {
        QString message("DomainSimulationBuilder::getSimulation() -> Error. Either MultiLayerItem "
                        " or InstrumentItem is not defined.");
        throw GUIHelpers::Error(message);
    }

    if (auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(instrumentItem)) {
        std::unique_ptr<GISASSimulation> gisas(new GISASSimulation);
        auto P_multilayer = DomainObjectBuilder::buildMultiLayer(*sampleItem);
        auto P_instrument = DomainObjectBuilder::buildInstrument(*gisasInstrument);
        gisas->setSample(*P_multilayer);
        gisas->setInstrument(*P_instrument);
        TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(), gisas.get());

        // Simulation options
        if (optionsItem)
            TransformToDomain::setSimulationOptions(gisas.get(), *optionsItem);

        // Background simulation
        auto P_background = gisasInstrument->backgroundItem()->createBackground();
        if (P_background)
            gisas->setBackground(*P_background);

        return std::unique_ptr<Simulation> (gisas.release());

    } else if (auto offspecInstrument = dynamic_cast<const OffSpecInstrumentItem*>(instrumentItem)) {
        std::unique_ptr<OffSpecSimulation> offspec(new OffSpecSimulation);
        auto P_multilayer = DomainObjectBuilder::buildMultiLayer(*sampleItem);
        auto P_instrument = DomainObjectBuilder::buildInstrument(*offspecInstrument);
        offspec->setSample(*P_multilayer);
        offspec->setInstrument(*P_instrument);

//        TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(), gisas.get());

        // Simulation options
        if (optionsItem)
            TransformToDomain::setSimulationOptions(offspec.get(), *optionsItem);

        // Background simulation
        auto P_background = offspecInstrument->backgroundItem()->createBackground();
        if (P_background)
            offspec->setBackground(*P_background);

        return std::unique_ptr<Simulation> (offspec.release());

    }

    throw GUIHelpers::Error("DomainSimulationBuilder::createSimulation() -> Error. Not yet implemented");
}
