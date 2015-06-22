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
#include "GUIHelpers.h"
#include <QDebug>


ParticleCoreShellItem::ParticleCoreShellItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleCoreShellType, parent)
{
    setItemName(Constants::ParticleCoreShellType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0),3));
    registerGroupProperty(ParticleItem::P_POSITION, Constants::VectorType);

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0, 1);
    addToValidChildren(Constants::ParticleType, PortInfo::PORT_1, 1);
}

void ParticleCoreShellItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    item->setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
    item->setPropertyAppearance(ParticleItem::P_ABUNDANCE, PropertyAttribute::DISABLED);
    int port = item->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
    if (port == ParameterizedItem::PortInfo::PORT_1) {
        ParameterizedItem *p_position_item = item->getSubItems()[ParticleItem::P_POSITION];
        p_position_item->setRegisteredProperty(VectorItem::P_X, 0.0);
        p_position_item->setRegisteredProperty(VectorItem::P_Y, 0.0);
        p_position_item->setRegisteredProperty(VectorItem::P_Z, 0.0);
        item->setPropertyAppearance(ParticleItem::P_POSITION, PropertyAttribute::DISABLED);
    }
}
