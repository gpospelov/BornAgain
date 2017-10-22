// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialModel.cpp
//! @brief     Implements class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialModel.h"
#include "MaterialUtils.h"
#include "GUIHelpers.h"
#include "MaterialDataItem.h"

MaterialModel::MaterialModel(QObject* parent) : SessionModel(SessionXML::MaterialModelTag, parent)
{
    setObjectName(SessionXML::MaterialModelTag);
}

MaterialModel* MaterialModel::createCopy(SessionItem* parent)
{
    MaterialModel* result = new MaterialModel();
    result->initFrom(this, parent);
    return result;
}

MaterialItem* MaterialModel::addMaterial(const QString& name, double material_data_real, double material_data_imag)
{
    MaterialItem* materialItem
        = dynamic_cast<MaterialItem*>(insertNewItem(Constants::HomogeneousMaterialType));
    materialItem->setItemName(name);

    MaterialDataItem* materialDataItem = dynamic_cast<MaterialDataItem*>(
        materialItem->getItem(MaterialItem::P_MATERIAL_DATA));
    Q_ASSERT(materialDataItem);

    materialDataItem->setReal(material_data_real);
    materialDataItem->setImag(material_data_imag);

    materialItem->setItemValue(MaterialItem::P_COLOR,
                               MaterialUtils::suggestMaterialColorProperty(name).getVariant());

    return materialItem;
}

void MaterialModel::removeMaterial(MaterialItem* item)
{
    QModelIndex materialIndex = indexOfItem(item);
    removeRows(materialIndex.row(), 1, materialIndex.parent());
}

MaterialItem* MaterialModel::getMaterial(const QModelIndex& index)
{
    return dynamic_cast<MaterialItem*>(itemForIndex(index));
}

MaterialItem* MaterialModel::getMaterial(const MaterialProperty& property)
{
    QModelIndex parentIndex;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);

        if (MaterialItem* material = dynamic_cast<MaterialItem*>(itemForIndex(itemIndex))) {
            if (material->getIdentifier() == property.getIdentifier())
                return material;
        }
    }
    return nullptr;
}

MaterialItem* MaterialModel::getMaterial(const QString& material_name)
{
    QModelIndex parentIndex;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);

        if (MaterialItem* material = dynamic_cast<MaterialItem*>(itemForIndex(itemIndex))) {
            if (material->itemName() == material_name)
                return material;
        }
    }
    return nullptr;
}

//! Returns clone of material with given index.

MaterialItem* MaterialModel::cloneMaterial(const QModelIndex& index)
{
    const MaterialItem* origMaterial = getMaterial(index);
    if (!origMaterial)
        return nullptr;

    SessionItem* clonedMaterial = copyParameterizedItem(origMaterial, 0);
    clonedMaterial->setItemValue(MaterialItem::P_IDENTIFIER, GUIHelpers::createUuid());
    clonedMaterial->setItemName(origMaterial->itemName() + " (clone)");
    return dynamic_cast<MaterialItem*>(clonedMaterial);
}
