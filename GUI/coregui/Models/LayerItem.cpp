// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LayerItem.cpp
//! @brief     Implements class LayerItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerItem.h"
#include "MaterialUtils.h"

const QString LayerItem::P_THICKNESS = "Thickness";
const QString LayerItem::P_ROUGHNESS = "Top roughness";
const QString LayerItem::P_MATERIAL = "Material";

LayerItem::LayerItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::LayerType, parent)
{
    setItemName(Constants::LayerType);
    registerProperty(P_THICKNESS, 0.0);
    registerProperty(P_MATERIAL, MaterialUtils::getDefaultMaterialProperty().getVariant());

    registerGroupProperty(P_ROUGHNESS, Constants::LayerRoughnessGroup);
    setGroupProperty(P_ROUGHNESS, Constants::LayerZeroRoughnessType);
    addToValidChildren(Constants::ParticleLayoutType, PortInfo::PORT_0);
}
