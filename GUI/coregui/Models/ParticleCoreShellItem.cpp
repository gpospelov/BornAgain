#include "ParticleCoreShellItem.h"


const QString ParticleCoreShellItem::P_TYPE_NAME = "ParticleCoreShell";
const QString ParticleCoreShellItem::P_CORE_X = "Core_X";
const QString ParticleCoreShellItem::P_CORE_Y = "Core_Y";
const QString ParticleCoreShellItem::P_CORE_Z = "Core_Z";


ParticleCoreShellItem::ParticleCoreShellItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(P_TYPE_NAME, parent)
{
    setItemName(P_TYPE_NAME);
    registerProperty(P_CORE_X, 0.0);
    registerProperty(P_CORE_Y, 0.0);
    registerProperty(P_CORE_Z, 0.0);

    m_valid_children.append(QString("Particle"));
}


