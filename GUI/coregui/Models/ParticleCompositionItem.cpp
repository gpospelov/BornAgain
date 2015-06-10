// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCompositionItem.cpp
//! @brief     Implements class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCompositionItem.h"
#include "ParticleItem.h"

ParticleCompositionItem::ParticleCompositionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleCompositionType, parent)
{
    setItemName(Constants::ParticleCompositionType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);

    registerProperty(ParticleItem::P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0),3));

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::PORT_0);
}

void ParticleCompositionItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    item->setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
    item->setPropertyAppearance(ParticleItem::P_ABUNDANCE, PropertyAttribute::DISABLED);
}
