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
#include "ParameterizedItem.h"
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

std::unique_ptr<MultiLayer> DomainObjectBuilder::buildMultiLayer(const ParameterizedItem &multilayer_item) const
{
    auto P_multilayer = TransformToDomain::createMultiLayer(multilayer_item);
    QList<ParameterizedItem *> children = multilayer_item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::LayerType) {
            auto P_layer = buildLayer(*children[i]);
            auto roughnessItem = children[i]->getSubItems()[LayerItem::P_ROUGHNESS];
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

std::unique_ptr<Layer> DomainObjectBuilder::buildLayer(const ParameterizedItem &item) const
{
    auto P_layer = TransformToDomain::createLayer(item);
    QList<ParameterizedItem *> children = item.childItems();
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
        const ParameterizedItem &item) const
{
    auto P_layout = TransformToDomain::createParticleLayout(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleType) {
            auto particle_item = children[i];
            auto P_particle = buildParticle(*particle_item);
            if (P_particle) {
                P_layout->addParticle(*P_particle);
            }
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            auto coreshell_item = children[i];
            auto P_coreshell = buildParticleCoreShell(*coreshell_item);
            if (P_coreshell) {
                P_layout->addParticle(*P_coreshell);
            }
        } else if (children[i]->modelType() == Constants::ParticleDistributionType) {
            auto prop
                = children[i]
                      ->getRegisteredProperty(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
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
                if (grandchildren[0]->modelType() == Constants::ParticleType) {
                    auto particle_item = grandchildren[0];
                    auto P_particle = buildParticle(*particle_item);
                    if (P_particle) {
                        P_layout->addParticle(*P_particle);
                    }
                } else if (grandchildren[0]->modelType() == Constants::ParticleCoreShellType) {
                    auto coreshell_item = grandchildren[0];
                    auto P_coreshell = buildParticleCoreShell(*coreshell_item);
                    if (P_coreshell) {
                        P_layout->addParticle(*P_coreshell);
                    }
                } else if (grandchildren[0]->modelType() == Constants::ParticleCompositionType) {
                    auto composition_item = grandchildren[0];
                    auto P_composition = buildParticleCoreShell(*composition_item);
                    if (P_composition) {
                        P_layout->addParticle(*P_composition);
                    }
                }
            } else {
                auto P_part_distr = buildParticleDistribution(*children[i]);
                if (P_part_distr) {
                    P_layout->addParticle(*P_part_distr);
                }
            }
        } else if (children[i]->modelType() == Constants::ParticleCompositionType) {
            auto P_part_coll = buildParticleComposition(*children[i]);
            if (P_part_coll) {
                P_layout->addParticle(*P_part_coll);
            }
        } else if (children[i]->modelType().startsWith("InterferenceFunction")) {
            auto P_interference = buildInterferenceFunction(*children[i]);
            if (P_interference) {
                P_layout->addInterferenceFunction(*P_interference);
            }
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                    " -> Error! Not implemented");
        }
    }
    return P_layout;
}

std::unique_ptr<Particle> DomainObjectBuilder::buildParticle(const ParameterizedItem &item) const
{
    auto& particle_item = static_cast<const ParticleItem&>(item);
    auto P_result = particle_item.createParticle();
    return P_result;
}

std::unique_ptr<ParticleCoreShell> DomainObjectBuilder::buildParticleCoreShell(
        const ParameterizedItem &item) const
{
    auto& particle_coreshell_item = static_cast<const ParticleCoreShellItem&>(item);
    auto P_coreshell = particle_coreshell_item.createParticleCoreShell();
    return P_coreshell;
}

std::unique_ptr<ParticleComposition> DomainObjectBuilder::buildParticleComposition(
        const ParameterizedItem &item) const
{
    auto& particle_composition_item = static_cast<const ParticleCompositionItem&>(item);
    auto P_composition = particle_composition_item.createParticleComposition();
    return P_composition;
}

//! Creates ParticleDistribution from parameterized item.
std::unique_ptr<ParticleDistribution>
DomainObjectBuilder::buildParticleDistribution(const ParameterizedItem &item,
                                               bool catch_errors) const
{
    auto children = item.childItems();
    if (children.size() == 0) {
        return nullptr;
    }
    std::unique_ptr<IParticle> P_particle;
    for(int i=0; i<children.size(); ++i) {
        ParameterizedItem *p_child = children[i];
        if (p_child->modelType() == Constants::ParticleType) {
            P_particle = buildParticle(*p_child);
            break;
        } else if (p_child->modelType() == Constants::ParticleCoreShellType) {
            P_particle = buildParticleCoreShell(*p_child);
            break;
        } else if (p_child->modelType() == Constants::ParticleCompositionType) {
            P_particle = buildParticleComposition(*p_child);
            break;
        }
    }
    if (!P_particle) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No correct particle defined");
    }
    auto distr_item = item.getSubItems()[ParticleDistributionItem::P_DISTRIBUTION];
    Q_ASSERT(distr_item);

    std::unique_ptr<IDistribution1D> P_distribution {};
    if(catch_errors) {
        try {
            P_distribution = TransformToDomain::createDistribution(*distr_item);
        } catch(const std::exception &ex) {
            qDebug() << "DomainObjectBuilder::buildParticleDistribution() -> Error."
                     << QString::fromStdString(ex.what());
            P_distribution = GUIHelpers::make_unique<DistributionGate>(1.0, 2.0);
        }
    } else {
        P_distribution = TransformToDomain::createDistribution(*distr_item);
    }

    auto prop = item.getRegisteredProperty(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER)
                    .value<ComboProperty>();
    QString par_name = prop.getValue();
    std::string domain_par = getDomainParameterName(par_name, *children[0], P_particle.get());
    int nbr_samples
        = distr_item->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigma_factor
        = distr_item->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();
    ParameterDistribution par_distr(domain_par, *P_distribution, nbr_samples, sigma_factor);
    auto result = GUIHelpers::make_unique<ParticleDistribution>(*P_particle, par_distr);
    double abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    result->setAbundance(abundance);
    return result;
}

std::unique_ptr<IInterferenceFunction>
DomainObjectBuilder::buildInterferenceFunction(const ParameterizedItem &item) const
{
    auto P_iff = TransformToDomain::createInterferenceFunction(item);
    Q_ASSERT(P_iff);
    return P_iff;
}

std::unique_ptr<Instrument> DomainObjectBuilder::buildInstrument(const ParameterizedItem &instrument_item) const
{
    auto P_instrument = TransformToDomain::createInstrument(instrument_item);
    QList<ParameterizedItem *> children = instrument_item.childItems();
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

std::unique_ptr<Beam> DomainObjectBuilder::buildBeam(const ParameterizedItem &item) const
{
    return TransformToDomain::createBeam(item);
}

std::string DomainObjectBuilder::getDomainParameterName(QString GUI_name,
                                                        const ParameterizedItem &item,
                                                        const IParticle *particle) const
{
    Q_UNUSED(item);
    Q_UNUSED(particle);
    return GUI_name.toStdString();
}
