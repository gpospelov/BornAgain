// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.cpp
//! @brief     Implements class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MaterialItem.h"
#include "ExternalProperty.h"
#include "GUIHelpers.h"
#include "MaterialDataItem.h"
#include "MaterialFactoryFuncs.h"
#include "SessionItemUtils.h"
#include "MaterialItemUtils.h"

using SessionItemUtils::GetVectorItem;

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

    ExternalProperty color = MaterialItemUtils::colorProperty(QColor(Qt::red));
    addProperty(P_COLOR, color.variant())->setEditorType(Constants::ColorEditorExternalType);

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
    ExternalProperty property = getItemValue(P_COLOR).value<ExternalProperty>();
    return property.color();
}

//TODO: make this function create proper type of material (refractive index m-l or wl-indp. mat-l)
std::unique_ptr<Material> MaterialItem::createMaterial() const
{
    const MaterialDataItem* materialDataItem
        = dynamic_cast<const MaterialDataItem*>(getItem(MaterialItem::P_MATERIAL_DATA));

    Q_ASSERT(materialDataItem);

    double real = materialDataItem->getReal();
    double imag = materialDataItem->getImag();

    auto magnetization = GetVectorItem(*this, P_MAGNETIZATION);

    return std::make_unique<Material>(HomogeneousMaterial(itemName().toStdString(), real, imag,
                                                 magnetization));
}
