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
#include "GUIHelpers.h"
#include "ParticleCoreShellItem.h"
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
    if (item.modelType() == QStringLiteral("MultiLayer")) {
        delete mp_sample;
        mp_sample = buildMultiLayer(item);
    }
    else if(item.modelType() == QStringLiteral("MultiLayer")) {
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
        else if(children[i]->modelType().startsWith("InterferenceFunction")) {
            boost::scoped_ptr<IInterferenceFunction>
                    interference(buildInterferenceFunction(*children[i]));
            if (interference.get()) {
                result->addInterferenceFunction(*interference);
            }
        }
        else if(children[i]->modelType() == ParticleCoreShellItem::P_TYPE_NAME) {
            double depth(0), abundance(0);
            boost::scoped_ptr<ParticleCoreShell>
                    coreshell(buildParticleCoreShell(*children[i], depth, abundance));
            if (coreshell.get()) {
                result->addParticle(*coreshell, depth, abundance);
            }
        }



        else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleLayout() -> Error! Not implemented");
        }
    }
    return result;
}


Particle *DomainObjectBuilder::buildParticle(const ParameterizedItem &item, double &depth, double &abundance) const
{
    Particle *result = TransformToDomain::createParticle(item, depth, abundance);
    return result;
}

IInterferenceFunction *DomainObjectBuilder::buildInterferenceFunction(const ParameterizedItem &item) const
{
    IInterferenceFunction *result = TransformToDomain::createInterferenceFunction(item);
    Q_ASSERT(result);
    return result;
}


Instrument *DomainObjectBuilder::buildInstrument(const ParameterizedItem &item) const
{
    qDebug() << "DomainObjectBuilder::buildInstrument";
    Instrument *result = TransformToDomain::createInstrument(item);
    QList<ParameterizedItem *> children = item.childItems();
    for (int i=0; i<children.size(); ++i) {
        qDebug() << "   DomainObjectBuilder::buildInstrument" << children[i]->modelType();
        if (children[i]->modelType() == QString("Beam")) {
            boost::scoped_ptr<Beam> P_beam(buildBeam(*children[i]));
            if (P_beam.get()) {
                result->setBeam(*P_beam);
            }
        }
        else if (children[i]->modelType() == QString("Detector")) {
            TransformToDomain::initInstrumentFromDetectorItem(*children[i], result);
        }

    }

    return result;
}

Beam *DomainObjectBuilder::buildBeam(const ParameterizedItem &item) const
{
    qDebug() << "DomainObjectBuilder::buildBeam()";
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
        if(port == ParameterizedItem::PortInfo::Port0) {
            coreParticle = buildParticle(*children[i], tmp_depth, tmp_abundance);
        }
        else if(port == ParameterizedItem::PortInfo::Port1) {
            shellParticle = buildParticle(*children[i], tmp_depth, tmp_abundance);
        }
        else {
            throw GUIHelpers::Error("DomainObjectBuilder::buildParticleCoreShell() -> Error. Logic error.");
        }
    }
    if(!coreParticle || !shellParticle)
        throw GUIHelpers::Error("DomainObjectBuilder::buildParticleCoreShell() -> Error. Logic error in p2.");

    ParticleCoreShell *result = TransformToDomain::createParticleCoreShell(item, *coreParticle, *shellParticle, depth, abundance);
    delete coreParticle;
    delete shellParticle;
    return result;
}


