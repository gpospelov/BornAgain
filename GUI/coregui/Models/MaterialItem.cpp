// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.cpp
//! @brief     Implements class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialItem.h"
#include "GUIHelpers.h"
#include "HomogeneousMaterial.h"
#include "MaterialDataItem.h"
#include "MaterialUtils.h"


namespace {
const QString magnetization_tooltip =
        "Magnetization (A/m)";
}

const QString MaterialItem::P_COLOR = "Color";
const QString MaterialItem::P_MATERIAL_DATA = "Material data";
const QString MaterialItem::P_MAGNETIZATION = "Magnetization";
const QString MaterialItem::P_IDENTIFIER = "Identifier";

MaterialItem::MaterialItem()
    : SessionItem(Constants::HomogeneousMaterialType)
{
    setItemName(Constants::HomogeneousMaterialType);

    ColorProperty color;
    addProperty(P_COLOR, color.getVariant());
    addGroupProperty(P_MATERIAL_DATA, Constants::MaterialDataType);
    addGroupProperty(P_MAGNETIZATION, Constants::VectorType)->setToolTip(magnetization_tooltip);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid());
    getItem(P_IDENTIFIER)->setVisible(false);
}

QString MaterialItem::getIdentifier() const
{
    return getItemValue(P_IDENTIFIER).toString();
}

QColor MaterialItem::getColor() const
{
    ColorProperty property = getItemValue(P_COLOR).value<ColorProperty>();
    return property.getColor();
}

std::unique_ptr<HomogeneousMaterial> MaterialItem::createMaterial() const
{
    const MaterialDataItem* materialDataItem
        = dynamic_cast<const MaterialDataItem*>(getItem(MaterialItem::P_MATERIAL_DATA));

    Q_ASSERT(materialDataItem);

    double real = materialDataItem->getReal();
    double imag = materialDataItem->getImag();

    auto magnetization = getVectorItem(P_MAGNETIZATION);

    return std::make_unique<HomogeneousMaterial>(itemName().toStdString(), real, imag,
                                                 magnetization);
}
