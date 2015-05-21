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
#include <boost/scoped_ptr.hpp>

MultiLayer *DomainObjectBuilder::buildMultiLayer(const ParameterizedItem &multilayer_item) const
{
    MultiLayer *result = TransformToDomain::createMultiLayer(multilayer_item);
    QList<ParameterizedItem *> children = multilayer_item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::LayerType) {
            boost::scoped_ptr<Layer> P_layer(buildLayer(*children[i]));

            ParameterizedItem *roughnessItem = children[i]->getSubItems()[LayerItem::P_ROUGHNESS];
            Q_ASSERT(roughnessItem);
            boost::scoped_ptr<LayerRoughness> P_roughness(
                TransformToDomain::createLayerRoughness(*roughnessItem));

            if (P_layer.get()) {
                if (P_roughness.get()) {
                    result->addLayerWithTopRoughness(*P_layer, *P_roughness);
                } else {
                    result->addLayer(*P_layer);
                }
            }
        }
    }
    return result;
}

Layer *DomainObjectBuilder::buildLayer(const ParameterizedItem &item) const
{
    Layer *result = TransformToDomain::createLayer(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleLayoutType) {
            boost::scoped_ptr<ParticleLayout> P_layout(buildParticleLayout(*children[i]));
            if (P_layout.get()) {
                result->addLayout(*P_layout);
            }
        }
    }
    return result;
}

ParticleLayout *DomainObjectBuilder::buildParticleLayout(const ParameterizedItem &item) const
{
    ParticleLayout *result = TransformToDomain::createParticleLayout(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        double depth(0.0), abundance(0.0);
        if (children[i]->modelType() == Constants::ParticleType) {
            ParameterizedItem *particle_item = children[i];
            boost::scoped_ptr<Particle> P_particle(buildParticle(*particle_item, depth, abundance));
            if (P_particle.get()) {
                addParticleToLayout(result, particle_item, depth, abundance, *P_particle);
            }
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            boost::scoped_ptr<ParticleCoreShell> P_coreshell(
                buildParticleCoreShell(*children[i], depth, abundance));
            if (P_coreshell.get()) {
                result->addParticle(*P_coreshell, depth, abundance);
            }
        } else if (children[i]->modelType() == Constants::ParticleDistributionType) {
            QVariant par_name_var = children[i]->getRegisteredProperty(
                        ParticleDistributionItem::P_DISTRIBUTED_PARAMETER);
            ComboProperty prop = par_name_var.value<ComboProperty>();
            QString par_name = prop.getValue();
            if (par_name == ParticleDistributionItem::NO_SELECTION) {
                QList<ParameterizedItem *> grandchildren = children[i]->childItems();
                if (grandchildren.size() == 0) {
                    continue;
                }
                if (grandchildren.size() > 1) {
                    throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                            " -> Error! Too many particles defined"
                                            " in ParticleDistribution");
                }
                if (grandchildren[0]->modelType() == Constants::ParticleType) {
                    ParameterizedItem *particle_item = grandchildren[0];
                    boost::scoped_ptr<Particle> P_particle(
                        buildParticle(*particle_item, depth, abundance));
                    if (P_particle.get()) {
                        addParticleToLayout(result, particle_item, depth, abundance, *P_particle);
                    }
                } else if (grandchildren[0]->modelType() == Constants::ParticleCoreShellType) {
                    boost::scoped_ptr<ParticleCoreShell> P_coreshell(
                        buildParticleCoreShell(*grandchildren[0], depth, abundance));
                    if (P_coreshell.get()) {
                        result->addParticle(*P_coreshell, depth, abundance);
                    }
                }
            } else {
                boost::scoped_ptr<ParticleDistribution> P_part_distr(
                            buildParticleDistribution(*children[i], depth, abundance));
                if (P_part_distr.get()) {
                    result->addParticle(*P_part_distr, depth, abundance);
                }
            }
        } else if (children[i]->modelType() == Constants::ParticleCompositionType) {
            boost::scoped_ptr<ParticleComposition> P_part_coll(
                buildParticleComposition(*children[i], abundance));
            if (P_part_coll.get()) {
                result->addParticle(*P_part_coll, 0.0, abundance);
            }
        } else if (children[i]->modelType().startsWith("InterferenceFunction")) {
            boost::scoped_ptr<IInterferenceFunction> P_interference(
                buildInterferenceFunction(*children[i]));
            if (P_interference.get()) {
                result->addInterferenceFunction(*P_interference);
            }
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                    " -> Error! Not implemented");
        }
    }
    return result;
}

Particle *DomainObjectBuilder::buildParticle(const ParameterizedItem &item, double &depth,
                                             double &abundance) const
{
    Particle *result = TransformToDomain::createParticle(item, depth, abundance);
    QList<ParameterizedItem *> children = item.childItems();
    if (children.size() > 1) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticle() "
                                "-> Error! ParticleItem has too many child items.");
    }
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::TransformationType) {
            RotationItem *rot_item = dynamic_cast<RotationItem *>(
                children[i]->getSubItems()[TransformationItem::P_ROT]);
            if (!rot_item) {
                throw GUIHelpers::Error("DomainObjectBuilder::buildParticle() "
                                        "-> Error! ParticleItem's child is"
                                        " not a transformation.");
            }
            boost::scoped_ptr<IRotation> P_rotation(rot_item->createRotation());
            if (P_rotation.get()) {
                result->setTransformation(*P_rotation);
            }
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticle() "
                                    "-> Error! Not implemented");
        }
    }
    return result;
}

ParticleCoreShell *DomainObjectBuilder::buildParticleCoreShell(const ParameterizedItem &item,
                                                               double &depth,
                                                               double &abundance) const
{
    QList<ParameterizedItem *> children = item.childItems();
    Particle *coreParticle(0);
    Particle *shellParticle(0);
    for (int i = 0; i < children.size(); ++i) {
        double tmp_depth(0), tmp_abundance(0);
        int port = children[i]->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
        if (port == ParameterizedItem::PortInfo::PORT_0) {
            coreParticle = buildParticle(*children[i], tmp_depth, tmp_abundance);
        } else if (port == ParameterizedItem::PortInfo::PORT_1) {
            shellParticle = buildParticle(*children[i], tmp_depth, tmp_abundance);
        } else {
            throw GUIHelpers::Error(
                "DomainObjectBuilder::buildParticleCoreShell() -> Error. Logic error.");
        }
    }
    if (!coreParticle || !shellParticle)
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleCoreShell() -> Error. Either "
                                "core or shell particle is undefined.");

    ParticleCoreShell *result = TransformToDomain::createParticleCoreShell(
        item, *coreParticle, *shellParticle, depth, abundance);
    delete coreParticle;
    delete shellParticle;
    return result;
}

ParticleComposition *DomainObjectBuilder::buildParticleComposition(const ParameterizedItem &item,
                                                                   double &abundance) const
{
    ParticleComposition *result
        = TransformToDomain::createParticleComposition(item, abundance);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        double tmp_depth(0.0), tmp_abundance(0.0);
        if (children[i]->modelType() == Constants::ParticleType) {
            ParameterizedItem *particle_item = children[i];
            boost::scoped_ptr<Particle> P_particle(
                buildParticle(*particle_item, tmp_depth, tmp_abundance));
            if (P_particle.get()) {
                addParticleToParticleComposition(result, particle_item, *P_particle); //TODO: add depth
            }
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            ParameterizedItem *particle_item = children[i];
            boost::scoped_ptr<ParticleCoreShell> P_coreshell(
                buildParticleCoreShell(*children[i], tmp_depth, tmp_abundance));
            if (P_coreshell.get()) {
                addParticleToParticleComposition(result, particle_item, *P_coreshell);
            }
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleComposition()"
                                    " -> Error! Not implemented");
        }
    }
    return result;
}

//! Creates ParticleDistribution from parameterized item. If catch_errors=true, then
//! possible misconfiguration of Distribution1D will be caught, fake distribution will be used
ParticleDistribution *DomainObjectBuilder::buildParticleDistribution(const ParameterizedItem &item,
                                                                     double &depth,
                                                                     double &abundance,
                                                                     bool catch_errors) const
{
    ParticleDistribution *p_result = 0;
    QList<ParameterizedItem *> children = item.childItems();
    if (children.size() == 0) {
        return p_result;
    }
    if (children.size() > 1) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! Too many particles defined");
    }
    boost::scoped_ptr<IParticle> P_particle;
    if (children[0]->modelType() == Constants::ParticleType) {
        ParameterizedItem *particle_item = children[0];
        P_particle.reset(buildParticle(*particle_item, depth, abundance));
    } else if (children[0]->modelType() == Constants::ParticleCoreShellType) {
        ParameterizedItem *particle_item = children[0];
        P_particle.reset(buildParticleCoreShell(*particle_item, depth, abundance));
    }
    if (!P_particle.get()) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No correct particle defined");
    }
    ParameterizedItem *distr_item = item.getSubItems()[ParticleDistributionItem::P_DISTRIBUTION];
    Q_ASSERT(distr_item);

    IDistribution1D *distr(0);
    if(catch_errors) {
        try {
            distr = TransformToDomain::createDistribution(*distr_item);
        } catch(const std::exception &ex) {
            qDebug() << "DomainObjectBuilder::buildParticleDistribution() -> Error."
                     << QString::fromStdString(ex.what());
            distr = new DistributionGate(1.0, 2.0);
        }
    } else {
        distr = TransformToDomain::createDistribution(*distr_item);
    }

    QVariant par_name_var
        = item.getRegisteredProperty(ParticleDistributionItem::P_DISTRIBUTED_PARAMETER);
    ComboProperty prop = par_name_var.value<ComboProperty>();
    QString par_name = prop.getValue();
    int nbr_samples
        = distr_item->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigma_factor
        = distr_item->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();
    ParameterDistribution par_distr(par_name.toStdString(), *distr, nbr_samples, sigma_factor);
    delete distr;
    p_result = new ParticleDistribution(*P_particle, par_distr);
    return p_result;
}

IInterferenceFunction *
DomainObjectBuilder::buildInterferenceFunction(const ParameterizedItem &item) const
{
    IInterferenceFunction *result = TransformToDomain::createInterferenceFunction(item);
    Q_ASSERT(result);
    return result;
}

Instrument *DomainObjectBuilder::buildInstrument(const ParameterizedItem &instrument_item) const
{
    Instrument *result = TransformToDomain::createInstrument(instrument_item);
    QList<ParameterizedItem *> children = instrument_item.childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::BeamType) {
            boost::scoped_ptr<Beam> P_beam(buildBeam(*children[i]));
            if (P_beam.get()) {
                result->setBeam(*P_beam);
            }
        } else if (children[i]->modelType() == Constants::DetectorType) {
            TransformToDomain::initInstrumentFromDetectorItem(*children[i], result);
        }
    }

    return result;
}

Beam *DomainObjectBuilder::buildBeam(const ParameterizedItem &item) const
{
    //    qDebug() << "DomainObjectBuilder::buildBeam()";
    Beam *result = TransformToDomain::createBeam(item);
    return result;
}

void DomainObjectBuilder::addParticleToLayout(ParticleLayout *result,
                                              ParameterizedItem *particle_item, double depth,
                                              double abundance, const Particle &particle) const
{
    QList<ParameterizedItem *> particle_children = particle_item->childItems();
    if (particle_children.size() > 1) {
        throw GUIHelpers::Error("DomainObjectBuilder::addParticleToLayout() "
                                "-> Error! ParticleItem has too many child items.");
    } else if (particle_children.size() == 0) {
        result->addParticle(particle, depth, abundance);
    } else {
        if (particle_children[0]->modelType() == Constants::TransformationType) {
            ParameterizedItem *pos_item
                = particle_children[0]->getSubItems()[TransformationItem::P_POS];
            double pos_x = pos_item->getRegisteredProperty(VectorItem::P_X).toDouble();
            double pos_y = pos_item->getRegisteredProperty(VectorItem::P_Y).toDouble();
            double pos_z = pos_item->getRegisteredProperty(VectorItem::P_Z).toDouble();
            if (pos_x != 0.0 || pos_y != 0.0 || pos_z != 0.0) {
                kvector_t position(pos_x, pos_y, pos_z);
                ParticleInfo particle_info(particle, position, abundance);
                result->addParticleInfo(particle_info);
            } else {
                result->addParticle(particle, depth, abundance);
            }
        } else {
            throw GUIHelpers::Error("DomainObjectBuilder::addParticleToLayout() "
                                    "-> Error! Not implemented");
        }
    }
}

void DomainObjectBuilder::addParticleToParticleComposition(ParticleComposition *result,
                                                           ParameterizedItem *particle_item,
                                                           const IParticle &particle) const
{
    double depth = particle_item->getRegisteredProperty(ParticleItem::P_DEPTH).toDouble();
    QList<ParameterizedItem *> particle_children = particle_item->childItems();
    kvector_t position;
    if (particle_children.size() == 1
        && particle_children[0]->modelType() == Constants::TransformationType) {
        ParameterizedItem *pos_item
            = particle_children[0]->getSubItems()[TransformationItem::P_POS];
        position.setX( pos_item->getRegisteredProperty(VectorItem::P_X).toDouble() );
        position.setY( pos_item->getRegisteredProperty(VectorItem::P_Y).toDouble() );
        position.setZ( pos_item->getRegisteredProperty(VectorItem::P_Z).toDouble() - depth );
        result->addParticle(particle, position);
    } else {
        position.setZ( -depth );
        result->addParticle(particle, position);
    }
}
