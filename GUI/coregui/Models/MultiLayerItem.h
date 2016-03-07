// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MultiLayerItem.h
//! @brief     Defines class MultiLayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERITEM_H
#define MULTILAYERITEM_H

#include "ParameterizedGraphicsItem.h"

class BA_CORE_API_ MultiLayerItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_CROSS_CORR_LENGTH;
    static const QString T_LAYERS;
    explicit MultiLayerItem();
    virtual ~MultiLayerItem() {}
    virtual ParameterizedItem *takeChildItem(int row);
    virtual void insertChildItem(int row, ParameterizedItem *item);

private:
    void updateLayers();
};

#endif // MULTILAYERITEM_H
