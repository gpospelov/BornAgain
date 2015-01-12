#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "GUIHelpers.h"
#include <QDebug>

const QString ParticleCoreShellItem::P_CORE_POS = "Core Position";


ParticleCoreShellItem::ParticleCoreShellItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleCoreShellType, parent)
{
    setItemName(Constants::ParticleCoreShellType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);
    registerProperty(ParticleItem::P_DEPTH, 0.0);
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0, PropertyAttribute(AttLimits::limited(0.0, 1.0),3));

    registerGroupProperty(P_CORE_POS, Constants::VectorType);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0, 1);
    addToValidChildren(Constants::ParticleType, PortInfo::PORT_1, 1);
}

void ParticleCoreShellItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    item->setPropertyAppearance(ParticleItem::P_ABUNDANCE, PropertyAttribute::DisabledProperty);
    item->setPropertyAppearance(ParticleItem::P_DEPTH, PropertyAttribute::DisabledProperty);
}
