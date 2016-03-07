// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LayerItem.cpp
//! @brief     Implements class LayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerItem.h"
#include "MaterialUtils.h"
#include "ComboProperty.h"

const QString LayerItem::P_THICKNESS = "Thickness";
const QString LayerItem::P_ROUGHNESS = "Top roughness";
const QString LayerItem::P_MATERIAL = "Material";
const QString LayerItem::T_LAYOUTS = "Layout tag";

LayerItem::LayerItem()
    : SessionGraphicsItem(Constants::LayerType)
{
    registerProperty(P_THICKNESS, 0.0);
    registerProperty(P_MATERIAL, MaterialUtils::getDefaultMaterialProperty().getVariant());

    registerGroupProperty(P_ROUGHNESS, Constants::LayerRoughnessGroup);
    setGroupProperty(P_ROUGHNESS, Constants::LayerZeroRoughnessType);
    registerTag(T_LAYOUTS, 0, -1, QStringList() << Constants::ParticleLayoutType);
    setDefaultTag(T_LAYOUTS);
}
