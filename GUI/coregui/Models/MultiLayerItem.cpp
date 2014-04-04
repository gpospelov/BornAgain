// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/MultiLayerItem.cpp
//! @brief     Implements class MultiLayerItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerItem.h"


MultiLayerItem::MultiLayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("MultiLayer"), parent)
{
    setProperty("Cross Correlation Length", 0.0);
    m_valid_children.append(QString("Layer"));
    m_valid_children.append(QString("MultiLayer"));
}

MultiLayerItem::~MultiLayerItem()
{
}
