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

#include <QDebug>

#include <boost/scoped_ptr.hpp>


DomainObjectBuilder::DomainObjectBuilder()
    : mp_sample(0)
    , m_instrument(0)
{

}

DomainObjectBuilder::~DomainObjectBuilder()
{
    delete mp_sample;
    delete m_instrument;
}

void DomainObjectBuilder::buildItem(const ParameterizedItem &item)
{
    if (item.modelType() == Constants::MultiLayerType) {
        delete mp_sample;
        mp_sample = buildMultiLayer(item);
    }
    else if(item.modelType() == Constants::InstrumentType) {
        delete m_instrument;
        m_instrument = buildInstrument(item);
    }
    else {
        throw GUIHelpers::Error("DomainObjectBuilder::buildItem() -> Error. Not a suitable top level object.");
    }
}

MultiLayer *DomainObjectBuilder::buildMultiLayer(
        const ParameterizedItem &item) const
{
    MultiLayer *result = TransformToDomain::createMultiLayer(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::LayerType) {
            boost::scoped_ptr<Layer> P_layer(buildLayer(*children[i]));

            ParameterizedItem *roughnessItem = children[i]->getSubItems()[LayerItem::P_ROUGHNESS];
            Q_ASSERT(roughnessItem);
            boost::scoped_ptr<LayerRoughness> P_roughness(TransformToDomain::createLayerRoughness(*roughnessItem));

            if (P_layer.get()) {
                if(P_roughness.get()) {
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
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleLayoutType) {
            boost::scoped_ptr<ParticleLayout>
                    P_layout(buildParticleLayout(*children[i]));
            if (P_layout.get()) {
                result->addLayout(*P_layout);
            }
        }
    }
    return result;
}


ParticleLayout *DomainObjectBuilder::buildParticleLayout(
        const ParameterizedItem &item) const
{
    ParticleLayout *result = TransformToDomain::createParticleLayout(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i=0; i<children.size(); ++i) {
        double depth(0.0), abundance(0.0);
        if (children[i]->modelType() == Constants::ParticleType) {
            ParameterizedItem *particle_item = children[i];
            boost::scoped_ptr<Particle>
                    particle(buildParticle(*particle_item, depth, abundance));
            if (particle.get()) {
                addParticleToLayout(result, particle_item, depth, abundance,
                                    *particle);
            }
        }
        else if(children[i]->modelType().startsWith("InterferenceFunction")) {
            boost::scoped_ptr<IInterferenceFunction>
                    interference(buildInterferenceFunction(*children[i]));
            if (interference.get()) {
                result->addInterferenceFunction(*interference);
            }
        }
        else if(children[i]->modelType() == Constants::ParticleCoreShellType) {
            boost::scoped_ptr<ParticleCoreShell>
                    coreshell(buildParticleCoreShell(*children[i], depth, abundance));
            if (coreshell.get()) {
                result->addParticle(*coreshell, depth, abundance);
            }
        }
        else if(children[i]->modelType() == Constants::ParticleDistributionType) {
            boost::scoped_ptr<ParticleDistribution>
                    part_distr(buildParticleDistribution(*children[i], depth,
                               abundance) );
            if (part_distr.get()) {
                result->addParticle(*part_distr, depth, abundance);
            }
        }
        else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout()"
                                    " -> Error! Not implemented");
        }
    }
    return result;
}


Particle *DomainObjectBuilder::buildParticle(const ParameterizedItem &item,
                                   double &depth, double &abundance) const
{
    Particle *result = TransformToDomain::createParticle(item, depth, abundance);
    QList<ParameterizedItem *> children = item.childItems();
    if (children.size()>1) {
        throw GUIHelpers::Error(
                "DomainObjectBuilder::buildParticle() "
                "-> Error! ParticleItem has too many child items.");
    }
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::TransformationType) {
            RotationItem *rot_item = dynamic_cast<RotationItem *>(
                children[i]->getSubItems()[TransformationItem::P_ROT]);
            if (!rot_item) {
                throw GUIHelpers::Error("DomainObjectBuilder::buildParticle() "
                                        "-> Error! ParticleItem's child is"
                                        " not a transformation.");
            }
            boost::scoped_ptr<Geometry::Transform3D> P_transform(
                        rot_item->createTransform());
            if (P_transform.get() && !P_transform->isIdentity()) {
                result->setTransformation(*P_transform);
            }
        }
        else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticle() "
                                    "-> Error! Not implemented");
        }
    }
    return result;
}

ParticleDistribution *DomainObjectBuilder::buildParticleDistribution(
        const ParameterizedItem &item, double &depth, double &abundance) const
{
    ParticleDistribution *p_result = 0;
    QList<ParameterizedItem *> children = item.childItems();
    if (children.size()!=1) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No particle defined");
    }
    boost::scoped_ptr<IParticle> P_particle;
    if (children[0]->modelType() == Constants::ParticleType) {
        ParameterizedItem *particle_item = children[0];
        P_particle.reset(buildParticle(*particle_item, depth, abundance));
    }
    else if (children[0]->modelType() == Constants::ParticleCoreShellType) {
        ParameterizedItem *particle_item = children[0];
        P_particle.reset(buildParticleCoreShell(*particle_item, depth,
                                                abundance));
    }
    if (!P_particle.get()) {
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleDistribution()"
                                " -> Error! No correct particle defined");
    }
    ParameterizedItem *distr_item =
            item.getSubItems()[ParticleDistributionItem::P_DISTRIBUTION];
    Q_ASSERT(distr_item);
    boost::scoped_ptr<IDistribution1D> distr(
                TransformToDomain::createDistribution(*distr_item) );
    QVariant par_name_var = item.getRegisteredProperty(
                ParticleDistributionItem::P_DISTRIBUTED_PARAMETER);
    ComboProperty prop = par_name_var.value<ComboProperty>();
    QString par_name = prop.getValue();
    int nbr_samples = item.getRegisteredProperty(
                ParticleDistributionItem::P_SAMPLE_NUMBER).toInt();
    double sigma_factor = item.getRegisteredProperty(
                ParticleDistributionItem::P_SIGMA_FACTOR).toDouble();
    ParameterDistribution par_distr(par_name.toStdString(), *distr,
                                    nbr_samples, sigma_factor);
    p_result = new ParticleDistribution(*P_particle, par_distr);
    return p_result;
}

IInterferenceFunction *DomainObjectBuilder::buildInterferenceFunction(
        const ParameterizedItem &item) const
{
    IInterferenceFunction *result = TransformToDomain::
            createInterferenceFunction(item);
    Q_ASSERT(result);
    return result;
}


Instrument *DomainObjectBuilder::buildInstrument(const ParameterizedItem &item) const
{
    Instrument *result = TransformToDomain::createInstrument(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::BeamType) {
            boost::scoped_ptr<Beam> P_beam(buildBeam(*children[i]));
            if (P_beam.get()) {
                result->setBeam(*P_beam);
            }
        }
        else if (children[i]->modelType() == Constants::DetectorType) {
            TransformToDomain::initInstrumentFromDetectorItem(*children[i],
                                                              result);
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

ParticleCoreShell *DomainObjectBuilder::buildParticleCoreShell(const ParameterizedItem &item, double &depth, double &abundance) const
{
    QList<ParameterizedItem *> children = item.childItems();
    Particle *coreParticle(0);
    Particle *shellParticle(0);
    for (int i=0; i<children.size(); ++i) {
        double tmp_depth(0), tmp_abundance(0);
        int port = children[i]->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
        if(port == ParameterizedItem::PortInfo::PORT_0) {
            coreParticle = buildParticle(*children[i], tmp_depth, tmp_abundance);
        }
        else if(port == ParameterizedItem::PortInfo::PORT_1) {
            shellParticle = buildParticle(*children[i], tmp_depth, tmp_abundance);
        }
        else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleCoreShell() -> Error. Logic error.");
        }
    }
    if(!coreParticle || !shellParticle)
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleCoreShell() -> Error. Either core or shell particle is undefined.");

    ParticleCoreShell *result = TransformToDomain::createParticleCoreShell(item, *coreParticle, *shellParticle, depth, abundance);
    delete coreParticle;
    delete shellParticle;
    return result;
}

void DomainObjectBuilder::addParticleToLayout(ParticleLayout *result,
    ParameterizedItem *particle_item, double depth, double abundance,
    const Particle& particle) const
{
    QList<ParameterizedItem *> particle_children =
            particle_item->childItems();
    if (particle_children.size()>1) {
        throw GUIHelpers::Error(
                "DomainObjectBuilder::buildParticleLayout() "
                "-> Error! ParticleItem has too many child items.");
    }
    if (particle_children.size()==0) {
        result->addParticle(particle, depth, abundance);
    }
    for (int i=0; i<particle_children.size(); ++i) {
        if (particle_children[i]->modelType() == Constants::TransformationType) {
            ParameterizedItem *pos_item = particle_children[i]->getSubItems()
                    [TransformationItem::P_POS];
            double pos_x = pos_item->getRegisteredProperty(
                        VectorItem::P_X).toDouble();
            double pos_y = pos_item->getRegisteredProperty(
                        VectorItem::P_Y).toDouble();
            double pos_z = pos_item->getRegisteredProperty(
                        VectorItem::P_Z).toDouble();
            if (pos_x!=0.0 || pos_y!=0.0 || pos_z!=0.0) {
                kvector_t position(pos_x, pos_y, pos_z);
                ParticleInfo particle_info(
                            particle, position, abundance);
                result->addParticleInfo(particle_info);
            } else {
                result->addParticle(particle, depth, abundance);
            }
        }
        else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticle() "
                                    "-> Error! Not implemented");
        }
    }
}



