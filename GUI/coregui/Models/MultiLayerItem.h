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

#include "ParameterizedItem.h"

class MultiLayerItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit MultiLayerItem(ParameterizedItem *parent=0);
    ~MultiLayerItem();
};

#endif // MULTILAYERITEM_H
