// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/DomainObjectBuilder.cpp
//! @brief     Implements class DomainObjectBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DomainObjectBuilder.h"
#include "TransformToDomain.h"

#include <boost/scoped_ptr.hpp>

DomainObjectBuilder::DomainObjectBuilder()
    : mp_sample(0)
{

}

DomainObjectBuilder::~DomainObjectBuilder()
{
    delete mp_sample;
}

void DomainObjectBuilder::buildItem(const ParameterizedItem &item)
{
    if (item.modelType() == QString("MultiLayer")) {
        delete mp_sample;
        mp_sample = buildMultiLayer(item);
    }
    else {
        // not a suitable top level object (throw?)
    }
}

MultiLayer *DomainObjectBuilder::buildMultiLayer(
        const ParameterizedItem &item) const
{
    MultiLayer *result = TransformToDomain::createMultiLayer(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == QString("Layer")) {
            boost::scoped_ptr<Layer> P_layer(buildLayer(*children[i]));
            if (P_layer.get()) {
                result->addLayer(*P_layer);
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
        if (children[i]->modelType() == QString("ParticleLayout")) {
            boost::scoped_ptr<ParticleLayout>
                    P_layout(buildParticleLayout(*children[i]));
            if (P_layout.get()) {
                result->setLayout(*P_layout);
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
        if (children[i]->modelType() == QString("Particle")) {
            double depth(0), abundance(0);
            boost::scoped_ptr<Particle>
                    particle(buildParticle(*children[i], depth, abundance));
            if (particle.get()) {
                result->addParticle(*particle, depth, abundance);
            }
        }
    }

    return result;
}


Particle *DomainObjectBuilder::buildParticle(const ParameterizedItem &item, double &depth, double &abundance) const
{
    Particle *particle = TransformToDomain::createParticle(item, depth, abundance);
    return particle;
}


