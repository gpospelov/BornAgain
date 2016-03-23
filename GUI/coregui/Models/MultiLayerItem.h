// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MultiLayerItem.h
//! @brief     Defines class MultiLayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERITEM_H
#define MULTILAYERITEM_H

#include "SessionGraphicsItem.h"

class BA_CORE_API_ MultiLayerItem : public SessionGraphicsItem
{

public:
    static const QString P_CROSS_CORR_LENGTH;
    static const QString T_LAYERS;
    explicit MultiLayerItem();
    virtual ~MultiLayerItem() {}

private:
    void updateLayers();
};

#endif // MULTILAYERITEM_H
