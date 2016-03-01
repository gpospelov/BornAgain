// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MultiLayerItem.cpp
//! @brief     Implements class MultiLayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "ScientificDoubleProperty.h"
#include "SessionModel.h"
#include <QDebug>

const QString MultiLayerItem::P_CROSS_CORR_LENGTH = "Cross Correlation Length";

MultiLayerItem::MultiLayerItem()
    : ParameterizedGraphicsItem(Constants::MultiLayerType)
{
    registerProperty(P_CROSS_CORR_LENGTH, 0.0);
    addToValidChildren(Constants::LayerType);
//    registerProperty(OBSOLETE_P_NAME, Constants::MultiLayerType);
    setItemName(Constants::MultiLayerType);
    mapper()->setOnChildrenChange(
                [this]()
    {
        updateLayers();
    });
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
    QList<ParameterizedItem*> list = getChildrenOfType(Constants::LayerType);
    for(auto it = list.begin(); it != list.end(); ++it) {
        if(it == list.begin()) {
            (*it)->getPropertyAttribute(LayerItem::P_ROUGHNESS).setDisabled();
        } else {
            (*it)->getPropertyAttribute(LayerItem::P_ROUGHNESS).setVisible();
        }
        if(it == list.begin() || it == list.end()) {
            (*it)->getPropertyAttribute(LayerItem::P_THICKNESS).setDisabled();
        } else {
            (*it)->getPropertyAttribute(LayerItem::P_THICKNESS).setVisible();
        }
    }
}
