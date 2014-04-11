// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleItem.h"
#include "FormFactorItems.h"

ParticleItem::ParticleItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("Particle"), parent)
{
    setItemName("ParticleName");
//    ParameterizedItem *p_ff = new CylinderItem();
//    addSubItem("Form Factor", p_ff);
    addFormFactorProperty("Form Factor", "Cylinder");
    setMaterialProperty();
    setProperty("Depth", 0.0);
    setProperty("Abundance", 1.0);
}

ParticleItem::~ParticleItem()
{
}
