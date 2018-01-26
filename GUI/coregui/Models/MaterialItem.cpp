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
#include "MaterialDataItems.h"
#include "MaterialFactoryFuncs.h"
#include "SessionItemUtils.h"
#include "MaterialItemUtils.h"
#include "GUIHelpers.h"

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
    : SessionItem(Constants::MaterialType)
{
    setItemName(Constants::MaterialType);

    ExternalProperty color = MaterialItemUtils::colorProperty(QColor(Qt::red));
    addProperty(P_COLOR, color.variant())->setEditorType(Constants::ColorEditorExternalType);

    addGroupProperty(P_MATERIAL_DATA, Constants::MaterialDataGroup);
    addGroupProperty(P_MAGNETIZATION, Constants::VectorType)->setToolTip(magnetization_tooltip);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid());
    getItem(P_IDENTIFIER)->setVisible(false);
}

//! Turns material into refractive index material.

void MaterialItem::setRefractiveData(double delta, double beta)
{
    auto refractiveData = setGroupProperty(P_MATERIAL_DATA, Constants::MaterialRefractiveDataType);
    refractiveData->setItemValue(MaterialRefractiveDataItem::P_DELTA, delta);
    refractiveData->setItemValue(MaterialRefractiveDataItem::P_BETA, beta);
}

void MaterialItem::setSLDData(double sld, double abs_term)
{
    auto sldData = setGroupProperty(P_MATERIAL_DATA, Constants::MaterialSLDDataType);
    sldData->setItemValue(MaterialRefractiveDataItem::P_DELTA, sld);
    sldData->setItemValue(MaterialRefractiveDataItem::P_BETA, abs_term);
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

std::unique_ptr<Material> MaterialItem::createMaterial() const
{
    auto dataItem = getGroupItem(P_MATERIAL_DATA);
    auto magnetization = GetVectorItem(*this, P_MAGNETIZATION);

    if (dataItem->modelType() == Constants::MaterialRefractiveDataType) {
        auto& materialDataItem = groupItem<MaterialRefractiveDataItem>(P_MATERIAL_DATA);

        double real = materialDataItem.delta();
        double imag = materialDataItem.beta();


        return std::make_unique<Material>(HomogeneousMaterial(itemName().toStdString(), real, imag,
                                                     magnetization));

    } else if(dataItem->modelType() == Constants::MaterialSLDDataType) {
        double sld = dataItem->getItemValue(MaterialSLDDataItem::P_SLD).toDouble();
        double abs_term = dataItem->getItemValue(MaterialSLDDataItem::P_ABS_TERM).toDouble();

        return std::make_unique<Material>(MaterialBySLD(itemName().toStdString(), sld, abs_term,
                                                     magnetization));
    }

    throw GUIHelpers::Error("MaterialItem::createMaterial() -> Error. "
                            "Not implemented material type");
}
