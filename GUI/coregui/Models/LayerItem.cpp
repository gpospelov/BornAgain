// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerItem.cpp
//! @brief     Implements class LayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LayerItem.h"
#include "BornAgainNamespace.h"
#include "MaterialUtils.h"

namespace {
const QString layer_nslices_tooltip =
    "Number of horizontal slices.\n"
    "Used for Average Layer Material calculations \n"
    "when corresponding Simulation option set.";
}

const QString LayerItem::P_THICKNESS = QString::fromStdString(BornAgain::Thickness);
const QString LayerItem::P_ROUGHNESS = "Top roughness";
const QString LayerItem::P_MATERIAL = "Material";
const QString LayerItem::P_NSLICES = "Number of slices";
const QString LayerItem::T_LAYOUTS = "Layout tag";

LayerItem::LayerItem()
    : SessionGraphicsItem(Constants::LayerType)
{
    setToolTip(QStringLiteral("A layer with thickness and material"));
    addProperty(P_THICKNESS, 0.0)->setLimits(RealLimits::lowerLimited(0.0))
        .setToolTip(QStringLiteral("Thickness of a layer in nanometers"));

    addProperty(P_MATERIAL, MaterialUtils::getDefaultMaterialProperty().getVariant())
            ->setToolTip(QStringLiteral("Material the layer is made of"));

    addProperty(P_NSLICES, 1)->setLimits(RealLimits::lowerLimited(0.0))
            .setToolTip(layer_nslices_tooltip);

    addGroupProperty(P_ROUGHNESS, Constants::LayerRoughnessGroup)
        ->setToolTip(QStringLiteral("Roughness of top interface"));

    registerTag(T_LAYOUTS, 0, -1, QStringList() << Constants::ParticleLayoutType);
    setDefaultTag(T_LAYOUTS);
}
