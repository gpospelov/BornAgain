// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MultiLayerItem.cpp
//! @brief     Implements class MultiLayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MultiLayerItem.h"
#include "BornAgainNamespace.h"
#include "LayerItem.h"

const QString MultiLayerItem::P_CROSS_CORR_LENGTH =
        QString::fromStdString(BornAgain::CrossCorrelationLength);
const QString MultiLayerItem::T_LAYERS = "Layer tag";

MultiLayerItem::MultiLayerItem()
    : SessionGraphicsItem(Constants::MultiLayerType)
{
    addProperty(P_CROSS_CORR_LENGTH, 0.0);
    registerTag(T_LAYERS, 0, -1, QStringList() << Constants::LayerType);
    setDefaultTag(T_LAYERS);
    setItemName(Constants::MultiLayerType);
    mapper()->setOnChildrenChange(
                [this](SessionItem*)
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
        if(it == list.begin() || it == (list.end()-1)) {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(false);
        } else {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(true);
        }
    }
}
