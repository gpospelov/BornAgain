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
#include "MaterialBrowser.h"

ParticleItem::ParticleItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("Particle"), parent)
{
    setItemName("ParticleName");
    setProperty("Form Factor", QString());
    MaterialProperty material = MaterialBrowser::getDefaultMaterialProperty();
    QVariant mat_var;
    mat_var.setValue(material);
    setProperty("Material", mat_var);
    setProperty("Depth", 0.0);
    setProperty("Abundance", 1.0);
}

ParticleItem::~ParticleItem()
{
}
