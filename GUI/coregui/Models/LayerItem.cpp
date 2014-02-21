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

LayerItem::LayerItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Layer"), parent)
{
    m_parameters[QString("Thickness")] = 0.0;
    m_valid_children.append(QString("ParticleDecoration"));
}

LayerItem::~LayerItem()
{
}
