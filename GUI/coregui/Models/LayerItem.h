// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/LayerItem.h
//! @brief     Defines class LayerItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERITEM_H
#define LAYERITEM_H

#include "ParameterizedItem.h"

class LayerItem : public ParameterizedItem
{
public:
    explicit LayerItem(ParameterizedItem *parent=0);
    ~LayerItem();
};

#endif // LAYERITEM_H

