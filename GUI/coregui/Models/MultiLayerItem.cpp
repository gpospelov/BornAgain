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

const QString MultiLayerItem::P_CROSS_CORR_LENGTH = "Cross Correlation Length";

MultiLayerItem::MultiLayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("MultiLayer"), parent)
{
    registerProperty(P_CROSS_CORR_LENGTH, 0.0);
    m_valid_children.append(QString("Layer"));
    m_valid_children.append(QString("MultiLayer"));

    //setPropertyVisibility(ParameterizedItem::P_NAME, ParameterizedItem::VisibleProperty);
    setPropertyAttribute(ParameterizedItem::P_NAME, ParameterizedItem::DefaultAttribute);
}

MultiLayerItem::~MultiLayerItem()
{
}
