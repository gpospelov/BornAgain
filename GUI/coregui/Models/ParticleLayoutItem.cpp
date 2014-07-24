// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleLayoutItem.cpp
//! @brief     Implements class ParticleLayoutItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleLayoutItem.h"
#include "ParticleCoreShellItem.h"

ParticleLayoutItem::ParticleLayoutItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleLayoutType, parent)
{
    setItemName(Constants::ParticleLayoutType);
    setItemPort(ParameterizedItem::PortInfo::Port0);
    addToValidChildren(Constants::ParticleType, PortInfo::Port0);
    addToValidChildren(Constants::ParticleCoreShellType, PortInfo::Port0);
    addToValidChildren(Constants::InterferenceFunction1DParaCrystalType, PortInfo::Port1, 1);
    addToValidChildren(Constants::InterferenceFunction2DParaCrystalType, PortInfo::Port1, 1);
}


ParticleLayoutItem::~ParticleLayoutItem()
{
}



