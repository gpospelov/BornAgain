// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainSimulationBuilder.cpp
//! @brief     Implements class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DomainSimulationBuilder.h"
#include "SampleModel.h"
#include "DocumentModel.h"
#include "InstrumentModel.h"
#include "Instrument.h"
#include "InstrumentItem.h"
#include "MultiLayer.h"
#include "MultiLayerItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "DomainObjectBuilder.h"
#include "TransformToDomain.h"
#include "SimulationOptionsItem.h"
#include "GUIHelpers.h"
#include <QDebug>
#include <memory>


//! Creates domain simulation from sample and instrument models. First sample and first instrument
//! in the model will be used, if there are more than one.
GISASSimulation *DomainSimulationBuilder::getSimulation(SampleModel *sampleModel,
        InstrumentModel *instrumentModel, DocumentModel *documentModel)
{
    MultiLayerItem *sampleItem = sampleModel->getMultiLayerItem();
    InstrumentItem *instrumentItem = instrumentModel->getInstrumentItem();
    SimulationOptionsItem *optionsItem = documentModel->getSimulationOptionsItem();
    return getSimulation(sampleItem, instrumentItem, optionsItem);
}

//! Creates domain simulation from sample and instrument items.
GISASSimulation *DomainSimulationBuilder::getSimulation(const MultiLayerItem *sampleItem,
                                                        const InstrumentItem *instrumentItem,
                                                        const SimulationOptionsItem *optionsItem)
{
    if(sampleItem == nullptr || instrumentItem==nullptr) {
        QString message("DomainSimulationBuilder::getSimulation() -> Error. Either MultiLayerItem "
                        " or InstrumentItem is not defined.");
        throw GUIHelpers::Error(message);
    }
    DomainObjectBuilder builder;

    GISASSimulation *result = new GISASSimulation;
    auto P_multilayer = builder.buildMultiLayer(*sampleItem);
    auto P_instrument = builder.buildInstrument(*instrumentItem);
    result->setSample(*P_multilayer);
    result->setInstrument(*P_instrument);

    TransformToDomain::addDistributionParametersToSimulation(*instrumentItem->getBeamItem(),
                                                             result);

    TransformToDomain::addMasksToSimulation(*instrumentItem->getDetectorItem(),
                                            result);

    if(optionsItem)
        TransformToDomain::setSimulationOptions(result, *optionsItem);

    return result;
}
