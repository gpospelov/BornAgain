#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "GUIHelpers.h"
#include <QDebug>

const QString ParticleCoreShellItem::P_CORE_POS = "Core Position";


ParticleCoreShellItem::ParticleCoreShellItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleCoreShellType, parent)
{
    setItemName(Constants::ParticleCoreShellType);
    setItemPort(ParameterizedItem::PortInfo::Port0);
    registerProperty(ParticleItem::P_DEPTH, 0.0);
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0);

    registerGroupProperty(P_CORE_POS, Constants::VectorType);

    addToValidChildren(Constants::ParticleType, PortInfo::Port0, 1);
    addToValidChildren(Constants::ParticleType, PortInfo::Port1, 1);
}

void ParticleCoreShellItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    item->setPropertyAttribute(ParticleItem::P_ABUNDANCE, PropertyAttribute::DisabledProperty);
    item->setPropertyAttribute(ParticleItem::P_DEPTH, PropertyAttribute::DisabledProperty);
}
