// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/LayerItem.cpp
//! @brief     Implements class LayerItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerItem.h"
#include "MaterialBrowser.h"

LayerItem::LayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("Layer"), parent)
{
    setItemName("LayerName");
    setProperty("Thickness", 0.0);
    setMaterialProperty();
    m_valid_children.append(QString("ParticleLayout"));
}

LayerItem::~LayerItem()
{
}
