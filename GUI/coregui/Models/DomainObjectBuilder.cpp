// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainObjectBuilder.cpp
//! @brief     Implements class DomainObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DomainObjectBuilder.h"
#include "TransformToDomain.h"
#include "GUIHelpers.h"
#include "ParticleCoreShellItem.h"
#include "Samples.h"
#include "Instrument.h"
#include "InterferenceFunctions.h"
#include "SessionItem.h"
#include "ParticleCoreShell.h"
#include "LayerItem.h"
#include "TransformationItem.h"
#include "VectorItem.h"
#include "RotationItems.h"
#include "ParticleDistributionItem.h"
#include "ParticleDistribution.h"
#include "Distributions.h"
#include "ComboProperty.h"
#include "MultiLayerItem.h"
#include "DistributionItem.h"
#include "ParticleItem.h"
#include "ParticleCompositionItem.h"

#include <QDebug>
#include <memory>

std::unique_ptr<MultiLayer> DomainObjectBuilder::buildMultiLayer(const SessionItem &multilayer_item) const
{
    auto P_multilayer = TransformToDomain::createMultiLayer(multilayer_item);
    QVector<SessionItem *> children = multilayer_item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::LayerType) {
            auto P_layer = buildLayer(*children[i]);
            auto roughnessItem = children[i]->getGroupItem(LayerItem::P_ROUGHNESS);
            Q_ASSERT(roughnessItem);
            auto P_roughness = TransformToDomain::createLayerRoughness(*roughnessItem);
            if (P_layer) {
                if (P_roughness) {
                    P_multilayer->addLayerWithTopRoughness(*P_layer, *P_roughness);
                } else {
                    P_multilayer->addLayer(*P_layer);
                }
            }
        }
    }
    return P_multilayer;
}

std::unique_ptr<Layer> DomainObjectBuilder::buildLayer(const SessionItem &item) const
{
    auto P_layer = TransformToDomain::createLayer(item);
    QVector<SessionItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleLayoutType) {
            auto P_layout = buildParticleLayout(*children[i]);
            if (P_layout) {
                P_layer->addLayout(*P_layout);
            }
        }
    }
    return P_layer;
}

std::unique_ptr<ParticleLayout> DomainObjectBuilder::buildParticleLayout(
        const SessionItem &item) const
{
    auto P_layout = TransformToDomain::createParticleLayout(item);
    QVector<SessionItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        auto P_particle = TransformToDomain::createIParticle(*children[i]);
        if (P_particle) {
            P_layout->addParticle(*P_particle);
            continue;
        }
        if (children[i]->modelType() == Constants::ParticleDistributionType) {
            auto prop
                = children[i]
                      ->getItemValue(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                      .value<ComboProperty>();
            QString par_name = prop.getValue();
            if (par_name == ParticleDistributionItem::NO_SELECTION) {
                auto grandchildren = children[i]->childItems();
                if (grandchildren.size() == 0) {
                    continue;
                }
                if (grandchildren.size() > 1) {
                    throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                            " -> Error! Too many particles defined"
                                            " in ParticleDistribution");
                }
                auto P_particle = TransformToDomain::createIParticle(*grandchildren[0]);
                if (P_particle) {
                    P_layout->addParticle(*P_particle);
                }
            } else {
                auto P_part_distr = TransformToDomain::createParticleDistribution(*children[i]);
                if (P_part_distr) {
                    P_layout->addParticle(*P_part_distr);
                }
            }
        } else if (children[i]->modelType().startsWith("Interference")) {
            auto P_interference = buildInterferenceFunction(*children[i]);
            if (P_interference) {
                P_layout->addInterferenceFunction(*P_interference);
            }
        } else {
//            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
//                                    " -> Error! Not implemented");
        }
    }
    return P_layout;
}

std::unique_ptr<IInterferenceFunction>
DomainObjectBuilder::buildInterferenceFunction(const SessionItem &item) const
{
    auto P_iff = TransformToDomain::createInterferenceFunction(item);
    Q_ASSERT(P_iff);
    return P_iff;
}

std::unique_ptr<Instrument> DomainObjectBuilder::buildInstrument(const SessionItem &instrument_item) const
{
    auto P_instrument = TransformToDomain::createInstrument(instrument_item);
    QVector<SessionItem *> children = instrument_item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::BeamType) {
            auto P_beam = buildBeam(*children[i]);
            if (P_beam) {
                P_instrument->setBeam(*P_beam);
            }
        } else if (children[i]->modelType() == Constants::DetectorType) {
            TransformToDomain::initInstrumentFromDetectorItem(*children[i], P_instrument.get());
        }
    }
    return P_instrument;
}

std::unique_ptr<Beam> DomainObjectBuilder::buildBeam(const SessionItem &item) const
{
    return TransformToDomain::createBeam(item);
}
