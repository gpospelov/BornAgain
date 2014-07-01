#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "GUIHelpers.h"
#include <QDebug>

const QString ParticleCoreShellItem::P_TYPE_NAME = "ParticleCoreShell";
const QString ParticleCoreShellItem::P_CORE_X = "Core_X";
const QString ParticleCoreShellItem::P_CORE_Y = "Core_Y";
const QString ParticleCoreShellItem::P_CORE_Z = "Core_Z";


ParticleCoreShellItem::ParticleCoreShellItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(P_TYPE_NAME, parent)
{
    setItemName(P_TYPE_NAME);
    setItemPort(ParameterizedItem::PortInfo::Port0);
    registerProperty(ParticleItem::P_DEPTH, 0.0);
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0);
    registerProperty(P_CORE_X, 0.0);
    registerProperty(P_CORE_Y, 0.0);
    registerProperty(P_CORE_Z, 0.0);

    addToValidChildren(QString("Particle"), PortInfo::Port0, 1);
    addToValidChildren(QString("Particle"), PortInfo::Port1, 1);
}
