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
#include "LayerItem.h"
#include <QDebug>

const QString MultiLayerItem::P_CROSS_CORR_LENGTH = "Cross Correlation Length";

MultiLayerItem::MultiLayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(QString("MultiLayer"), parent)
{
    registerProperty(P_CROSS_CORR_LENGTH, 0.0);
    addToValidChildren(QString("Layer"));
    addToValidChildren(QString("MultiLayer"));

    setPropertyAttribute(ParameterizedItem::P_NAME, ParameterizedItem::DefaultAttribute);
}

ParameterizedItem *MultiLayerItem::takeChildItem(int row)
{
    ParameterizedItem *item = ParameterizedItem::takeChildItem(row);
    updateLayers();
    return item;
}


void MultiLayerItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    updateLayers();
}

void MultiLayerItem::updateLayers()
{
    for(int i = 0; i<childItemCount(); ++i) {
        if(i == 0) {
            childAt(i)->setPropertyAttribute(LayerItem::P_ROUGHNESS, ParameterizedItem::DisabledProperty);
        } else {
            childAt(i)->setPropertyAttribute(LayerItem::P_ROUGHNESS, ParameterizedItem::DefaultAttribute);
        }
    }
}

