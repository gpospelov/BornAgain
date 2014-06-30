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
    : ParameterizedGraphicsItem(QString("ParticleLayout"), parent)
{
    addToValidChildrenX(QString("Particle"), PortInfo::Port0);
    addToValidChildrenX(ParticleCoreShellItem::P_TYPE_NAME, PortInfo::Port0);
    addToValidChildrenX(QString("InterferenceFunction1DParaCrystal"), PortInfo::Port1, 1);
    addToValidChildrenX(QString("InterferenceFunction2DParaCrystal"), PortInfo::Port1, 1);
}


ParticleLayoutItem::~ParticleLayoutItem()
{
}



