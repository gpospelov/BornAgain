#include "TransformationItem.h"
#include "ParticleItem.h"
#include "GUIHelpers.h"
#include <QDebug>

const QString TransformationItem::P_POS = "Position";
const QString TransformationItem::P_ROT = "Rotation";


TransformationItem::TransformationItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::TransformationType, parent)
{
    setItemName(Constants::TransformationType);
    setItemPort(ParameterizedItem::PortInfo::Port0);

    registerGroupProperty(P_POS, Constants::VectorType);
    registerGroupProperty(P_ROT, Constants::VectorType);
}

