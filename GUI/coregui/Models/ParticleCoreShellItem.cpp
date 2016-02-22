// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCoreShellItem.cpp
//! @brief     Implements class ParticleCoreShellItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "VectorItem.h"
#include "TransformToDomain.h"
#include "GUIHelpers.h"
#include <QDebug>

ParticleCoreShellItem::ParticleCoreShellItem()
    : ParameterizedGraphicsItem(Constants::ParticleCoreShellType)
{
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0).limited(0.0, 1.0).setDecimals(3);
    registerGroupProperty(ParticleItem::P_POSITION, Constants::VectorType);
    PositionTranslator position_translator;
    addParameterTranslator(position_translator);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0, 1); // Core particle
    addToValidChildren(Constants::ParticleType, PortInfo::PORT_1, 1); // Shell particle
    addToValidChildren(Constants::TransformationType, PortInfo::PORT_2, 1);
    RotationTranslator rotation_translator;
    addParameterTranslator(rotation_translator);
}

void ParticleCoreShellItem::insertChildItem(int row, ParameterizedItem *item)
{
//    int port = item->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();
    int port = int(item->port());
    PortInfo::EPorts first_available_particle_port = getFirstAvailableParticlePort();
    ParameterizedItem::insertChildItem(row, item);
    if (item->modelType() == Constants::ParticleType && port == PortInfo::DEFAULT
        && first_available_particle_port != PortInfo::DEFAULT) {
        item->setPort(first_available_particle_port);
    } else if (item->modelType() == Constants::TransformationType && port == PortInfo::DEFAULT) {
        item->setPort(PortInfo::PORT_2);
    }
}

void ParticleCoreShellItem::onPropertyChange(const QString &name)
{
    ParameterizedItem::onPropertyChange(name);
    if (name == "OBSOLETE_P_PORT" && parent()) {
        if (parent()->modelType() == Constants::ParticleCompositionType
            || parent()->modelType() == Constants::ParticleDistributionType) {
            setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
            getPropertyAttribute(ParticleItem::P_ABUNDANCE).setDisabled();
        }
    }
}

std::unique_ptr<ParticleCoreShell> ParticleCoreShellItem::createParticleCoreShell() const
{
    double abundance = getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    auto children = childItems();
    std::unique_ptr<Particle> P_core {};
    std::unique_ptr<Particle> P_shell {};
    for (int i = 0; i < children.size(); ++i) {
//        int port = children[i]->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();
        int port = children[i]->port();
        if (port == ParameterizedItem::PortInfo::PORT_0) {
            auto core_item = static_cast<ParticleItem*>(children[i]);
            P_core = core_item->createParticle();
        } else if (port == ParameterizedItem::PortInfo::PORT_1) {
            auto shell_item = static_cast<ParticleItem*>(children[i]);
            P_shell = shell_item->createParticle();
        } else if (port == ParameterizedItem::PortInfo::PORT_2) {
            continue;
        } else {
            throw GUIHelpers::Error(
                "ParticleCoreShellItem::createParticleCoreShell -> Error. Logic error.");
        }
    }
    if (!P_core || !P_shell)
        throw GUIHelpers::Error("ParticleCoreShellItem::createParticleCoreShell -> Error. Either "
                                "core or shell particle is undefined.");
    auto P_coreshell = GUIHelpers::make_unique<ParticleCoreShell>(*P_shell, *P_core);
    P_coreshell->setAbundance(abundance);
    TransformToDomain::setTransformationInfo(P_coreshell.get(), *this);
    return P_coreshell;
}

void ParticleCoreShellItem::notifyChildParticlePortChanged()
{
    QList<ParameterizedItem *> children = childItems();
    int core_index = -1;
    int shell_index = -1;
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleType) {
            PortInfo::EPorts port = children[i]->port();/*(PortInfo::EPorts)children[i]
                                        ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();*/
            if (port == PortInfo::PORT_0) core_index = i;
            if (port == PortInfo::PORT_1) shell_index = i;
        }
    }
    if (shell_index >= 0 && core_index > shell_index) {
        swapChildren(core_index, shell_index);
    }
}

ParameterizedItem::PortInfo::EPorts ParticleCoreShellItem::getFirstAvailableParticlePort() const
{
    // Also when no ports are available, return the first port (core particle will then be replaced)
    PortInfo::EPorts result = PortInfo::PORT_0;
    QList<PortInfo::EPorts> used_particle_ports;
    QList<ParameterizedItem *> children = childItems();
    for (auto item : children) {
        if (item->modelType() == Constants::ParticleType) {
            PortInfo::EPorts port = item->port();
//                = (PortInfo::EPorts)item->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();
            used_particle_ports.append(port);
        }
    }
    if (used_particle_ports.size() < 2) {
        if (used_particle_ports.contains(PortInfo::PORT_0)) {
            result = PortInfo::PORT_1;
        }
    }
    return result;
}
