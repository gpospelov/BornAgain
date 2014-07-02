// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/MultiLayerItem.h
//! @brief     Defines class MultiLayerItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERITEM_H
#define MULTILAYERITEM_H

#include "ParameterizedGraphicsItem.h"

class MultiLayerItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_CROSS_CORR_LENGTH;
    explicit MultiLayerItem(ParameterizedItem *parent=0);
    ~MultiLayerItem(){}
    void insertChildItem(int row, ParameterizedItem *item);
};

#endif // MULTILAYERITEM_H
