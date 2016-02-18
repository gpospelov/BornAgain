// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LayerItem.h
//! @brief     Defines class LayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERITEM_H
#define LAYERITEM_H

#include "ParameterizedGraphicsItem.h"

class BA_CORE_API_ LayerItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_THICKNESS;
    static const QString P_ROUGHNESS;
    static const QString P_MATERIAL;
    explicit LayerItem();
    virtual ~LayerItem(){}
    virtual void insertChild(int row, ParameterizedItem *item);
};

#endif // LAYERITEM_H

