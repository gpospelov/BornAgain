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
const QString MultiLayerItem::T_LAYERS = "Layer tag";

MultiLayerItem::MultiLayerItem()
    : SessionGraphicsItem(Constants::MultiLayerType)
{
    addProperty(P_CROSS_CORR_LENGTH, 0.0);
    registerTag(T_LAYERS, 0, -1, QStringList() << Constants::LayerType);
    setDefaultTag(T_LAYERS);
    setItemName(Constants::MultiLayerType);
    mapper()->setOnChildrenChange(
                [this]()
    {
        updateLayers();
    });
}

void MultiLayerItem::updateLayers()
{
    QVector<SessionItem*> list = getChildrenOfType(Constants::LayerType);
    for(auto it = list.begin(); it != list.end(); ++it) {
        if(it == list.begin()) {
            (*it)->getItem(LayerItem::P_ROUGHNESS)->setEnabled(false);
        } else {
            (*it)->getItem(LayerItem::P_ROUGHNESS)->setEnabled(true);
        }
        if(it == list.begin() || it == list.end()) {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(false);
        } else {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(true);
        }
    }
}
