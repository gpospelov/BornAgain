// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerItem.h
//! @brief     Defines class LayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LAYERITEM_H
#define LAYERITEM_H

#include "GUI/coregui/Models/SessionGraphicsItem.h"

class BA_CORE_API_ LayerItem : public SessionGraphicsItem
{
public:
    static const QString P_THICKNESS;
    static const QString P_ROUGHNESS;
    static const QString P_MATERIAL;
    static const QString P_NSLICES;
    static const QString T_LAYOUTS;
    LayerItem();

    QVector<SessionItem*> materialPropertyItems();

private:
    void updateAppearance(SessionItem* new_parent);
};

#endif // LAYERITEM_H
