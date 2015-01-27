// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformationItem.cpp
//! @brief     Implements class TransformationItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
    setItemPort(ParameterizedItem::PortInfo::PORT_0);

    registerGroupProperty(P_POS, Constants::VectorType);
    registerGroupProperty(P_ROT, Constants::RotationGroup );
}

