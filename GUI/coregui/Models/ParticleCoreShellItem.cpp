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
#include "ModelPath.h"
#include <QDebug>

const QString ParticleCoreShellItem::T_CORE = "Core Tag";
const QString ParticleCoreShellItem::T_SHELL = "Shell Tag";

ParticleCoreShellItem::ParticleCoreShellItem()
    : SessionGraphicsItem(Constants::ParticleCoreShellType)
{
    addProperty(ParticleItem::P_ABUNDANCE, 1.0);
    getItem(ParticleItem::P_ABUNDANCE)->setLimits(AttLimits::limited(0.0, 1.0));
    getItem(ParticleItem::P_ABUNDANCE)->setDecimals(3);
    addGroupProperty(ParticleItem::P_POSITION, Constants::VectorType);
    PositionTranslator position_translator;
    ModelPath::addParameterTranslator(position_translator);

    registerTag(T_CORE, 0, 1, QStringList() << Constants::ParticleType);
    registerTag(T_SHELL, 0, 1, QStringList() << Constants::ParticleType);
    registerTag(ParticleItem::T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);
    RotationTranslator rotation_translator;
    ModelPath::addParameterTranslator(rotation_translator);
    mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        // FIXME not working now because port is not a property anymore
        if (name == "OBSOLETE_P_PORT" && parent()) {
            if (parent()->modelType() == Constants::ParticleCompositionType
                || parent()->modelType() == Constants::ParticleDistributionType) {
                setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
                getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
            }
        }
    });
}

std::unique_ptr<ParticleCoreShell> ParticleCoreShellItem::createParticleCoreShell() const
{
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    auto children = childItems();
    std::unique_ptr<Particle> P_core {};
    std::unique_ptr<Particle> P_shell {};
    auto core_item = dynamic_cast<ParticleItem*>(getItem(T_CORE));
    if (core_item)
        P_core = core_item->createParticle();
    auto shell_item = dynamic_cast<ParticleItem*>(getItem(T_SHELL));
    if (shell_item)
        P_shell = shell_item->createParticle();
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
    // TODO restore logic
//    QVector<SessionItem *> children = childItems();
//    int core_index = -1;
//    int shell_index = -1;
//    for (int i=0; i<children.size(); ++i) {
//        if (children[i]->modelType() == Constants::ParticleType) {
//            PortInfo::EPorts port = children[i]->port();/*(PortInfo::EPorts)children[i]
//                                        ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();*/
//            if (port == PortInfo::PORT_0) core_index = i;
//            if (port == PortInfo::PORT_1) shell_index = i;
//        }
//    }
//    if (shell_index >= 0 && core_index > shell_index) {
//        swapChildren(core_index, shell_index);
//    }
}

//! TODO where is it used? restore logic
//ParameterizedItem::PortInfo::EPorts ParticleCoreShellItem::getFirstAvailableParticlePort() const
//{
//    // Also when no ports are available, return the first port (core particle will then be replaced)
//    PortInfo::EPorts result = PortInfo::PORT_0;
//    QList<PortInfo::EPorts> used_particle_ports;
//    QVector<SessionItem *> children = childItems();
//    for (auto item : children) {
//        if (item->modelType() == Constants::ParticleType) {
//            PortInfo::EPorts port = item->port();
////                = (PortInfo::EPorts)item->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();
//            used_particle_ports.append(port);
//        }
//    }
//    if (used_particle_ports.size() < 2) {
//        if (used_particle_ports.contains(PortInfo::PORT_0)) {
//            result = PortInfo::PORT_1;
//        }
//    }
//    return result;
//}
