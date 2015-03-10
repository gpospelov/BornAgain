// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCollectionItem.cpp
//! @brief     Implements class ParticleCollectionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCollectionItem.h"
#include "ParticleItem.h"

ParticleCollectionItem::ParticleCollectionItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleCollectionType, parent)
{
    setItemName(Constants::ParticleCollectionType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);

    registerProperty(ParticleItem::P_DEPTH, 0.0);
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0),3));

    addToValidChildren(Constants::ParticleType, PortInfo::PORT_0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::PORT_0);
}

ParticleCollectionItem::~ParticleCollectionItem()
{
}

