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

std::unique_ptr<ParticleLayout> DomainObjectBuilder::buildParticleLayout(const ParameterizedItem &item) const
{
    auto P_layout = TransformToDomain::createParticleLayout(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        double abundance(0.0);
        if (children[i]->modelType() == Constants::ParticleType) {
            auto particle_item = children[i];
            auto P_particle = buildParticle(*particle_item, abundance);
            if (P_particle) {
                P_layout->addParticle(*P_particle, abundance);
            }
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            auto coreshell_item = children[i];
            auto P_coreshell = buildParticleCoreShell(*coreshell_item, abundance);
            if (P_coreshell) {
                P_layout->addParticle(*P_coreshell, abundance);
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
                    particle_item->print();
                    auto P_particle = buildParticle(*particle_item, abundance);
                    if (P_particle) {
                        P_layout->addParticle(*P_particle, abundance);
                    }
                } else if (grandchildren[0]->modelType() == Constants::ParticleCoreShellType) {
                    auto coreshell_item = grandchildren[0];
                    auto P_coreshell = buildParticleCoreShell(*coreshell_item, abundance);
                    if (P_coreshell) {
                        P_layout->addParticle(*P_coreshell, abundance);
                    }
                }
            } else {
                auto P_part_distr = buildParticleDistribution(*children[i], abundance);
                if (P_part_distr) {
                    P_layout->addParticle(*P_part_distr, abundance);
                }
            }
        } else if (children[i]->modelType() == Constants::ParticleCompositionType) {
            auto P_part_coll = buildParticleComposition(*children[i], abundance);
            if (P_part_coll) {
                P_layout->addParticle(*P_part_coll, abundance);
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

std::unique_ptr<Particle> DomainObjectBuilder::buildParticle(const ParameterizedItem &item,
                                                             double &abundance) const
{
    auto P_result = TransformToDomain::createParticle(item, abundance);
    setTransformationInfo(P_result.get(), item);
    return P_result;
}

std::unique_ptr<ParticleCoreShell> DomainObjectBuilder::buildParticleCoreShell(const ParameterizedItem &item,
                                                               double &abundance) const
{
    auto children = item.childItems();
    std::unique_ptr<Particle> P_core {};
    std::unique_ptr<Particle> P_shell {};
    for (int i = 0; i < children.size(); ++i) {
        double tmp_abundance(0);
        int port = children[i]->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
        if (port == ParameterizedItem::PortInfo::PORT_0) {
            P_core = buildParticle(*children[i], tmp_abundance);
        } else if (port == ParameterizedItem::PortInfo::PORT_1) {
            P_shell = buildParticle(*children[i], tmp_abundance);
        } else if (port == ParameterizedItem::PortInfo::PORT_2) {
            continue;
        } else {
            throw GUIHelpers::Error(
                "DomainObjectBuilder::buildParticleCoreShell() -> Error. Logic error.");
        }
    }
    if (!P_core || !P_shell)
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleCoreShell() -> Error. Either "
                                "core or shell particle is undefined.");

    auto P_coreshell = TransformToDomain::createParticleCoreShell(item, *P_core, *P_shell,
                                                                  abundance);
    setTransformationInfo(P_coreshell.get(), item);
    return P_coreshell;
}

std::unique_ptr<ParticleComposition> DomainObjectBuilder::buildParticleComposition(
        const ParameterizedItem &item, double &abundance) const
{
    auto P_composition = TransformToDomain::createParticleComposition(item, abundance);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        double tmp_abundance(0.0);
        if (children[i]->modelType() == Constants::ParticleType) {
            ParameterizedItem *particle_item = children[i];
            std::unique_ptr<Particle> P_particle { buildParticle(*particle_item, tmp_abundance) };
            if (P_particle) {
                P_composition->addParticle(*P_particle);
            }
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            ParameterizedItem *particle_item = children[i];
            std::unique_ptr<ParticleCoreShell> P_coreshell {
                buildParticleCoreShell(*particle_item, tmp_abundance) };
            if (P_coreshell) {
                P_composition->addParticle(*P_coreshell);
            }
        } else if (children[i]->modelType() == Constants::ParticleCompositionType) {
            ParameterizedItem *particle_item = children[i];
            std::unique_ptr<ParticleComposition> P_composition {
                buildParticleComposition(*particle_item, tmp_abundance) };
            if (P_composition) {
                P_composition->addParticle(*P_composition);
            }
        } else if (children[i]->modelType() == Constants::TransformationType) {
            continue;
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleComposition()"
                                    " -> Error! Not implemented");
        }
    }
    setTransformationInfo(P_composition.get(), item);
    return P_composition;
}

//! Creates ParticleDistribution from parameterized item.
std::unique_ptr<ParticleDistribution>
DomainObjectBuilder::buildParticleDistribution(const ParameterizedItem &item,
                                               double &abundance,
                                               bool catch_errors) const
{
    auto children = item.childItems();
    if (children.size() == 0) {
        return nullptr;
    }
    std::unique_ptr<IParticle> P_particle;
    abundance = item.getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    double disabled_abundance(0);
    for(int i=0; i<children.size(); ++i) {
        ParameterizedItem *p_child = children[i];
        if (p_child->modelType() == Constants::ParticleType) {
            P_particle = buildParticle(*p_child, disabled_abundance);
            break;
        } else if (p_child->modelType() == Constants::ParticleCoreShellType) {
            P_particle = buildParticleCoreShell(*p_child, disabled_abundance);
            break;
        } else if (p_child->modelType() == Constants::ParticleCompositionType) {
            P_particle = buildParticleComposition(*p_child, disabled_abundance);
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
    return GUIHelpers::make_unique<ParticleDistribution>(*P_particle, par_distr);
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

void DomainObjectBuilder::setTransformationInfo(IParticle *result,
                                                const ParameterizedItem &item) const
{
    setPositionInfo(result, item);
    setRotationInfo(result, item);
}

void DomainObjectBuilder::setPositionInfo(IParticle *result,
                                          const ParameterizedItem &item) const
{
    ParameterizedItem *pos_item = item.getSubItems()[ParticleItem::P_POSITION];
    double pos_x = pos_item->getRegisteredProperty(VectorItem::P_X).toDouble();
    double pos_y = pos_item->getRegisteredProperty(VectorItem::P_Y).toDouble();
    double pos_z = pos_item->getRegisteredProperty(VectorItem::P_Z).toDouble();
    result->setPosition(pos_x, pos_y, pos_z);
}

void DomainObjectBuilder::setRotationInfo(IParticle *result, const ParameterizedItem &item) const
{
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::TransformationType) {
            RotationItem *rot_item = dynamic_cast<RotationItem *>(
                children[i]->getSubItems()[TransformationItem::P_ROT]);
            if (!rot_item) {
                throw GUIHelpers::Error("DomainObjectBuilder::setRotationInfo() "
                                        "-> Error! ParticleItem's child is"
                                        " not a rotation.");
            }
            std::unique_ptr<IRotation> P_rotation(rot_item->createRotation());
            if (P_rotation.get()) {
                result->setRotation(*P_rotation);
            }
            break;
        }
    }
}

