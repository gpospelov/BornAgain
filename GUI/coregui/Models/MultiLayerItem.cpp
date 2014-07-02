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


void MultiLayerItem::insertChildItem(int row, ParameterizedItem *item)
{
    if(row == 0) {
        qDebug() << " ";
        qDebug() << " ";
        qDebug() << " XXX MultiLayerItem::insertChildItem ";
        item->print();
        item->setGroupProperty(LayerItem::P_ROUGHNESS, "No");
        item->setPropertyAttribute(LayerItem::P_ROUGHNESS, ParameterizedItem::DisabledProperty);
        qDebug() << " after";
        item->print();

    }

    ParameterizedItem::insertChildItem(row, item);
}
