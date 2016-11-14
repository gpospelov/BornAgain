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
#include "IconProvider.h"
#include "MaterialUtils.h"
#include "RefractiveIndexItem.h"
#include "GUIHelpers.h"
#include <QDebug>

MaterialModel::MaterialModel(QObject *parent)
    : SessionModel(SessionXML::MaterialModelTag, parent)
{
    setObjectName(SessionXML::MaterialModelTag);
    setIconProvider(new IconProvider());
}

MaterialModel *MaterialModel::createCopy(SessionItem *parent)
{
    MaterialModel *result = new MaterialModel();
    result->initFrom(this, parent);
    return result;
}

MaterialItem *MaterialModel::addMaterial(const QString &name, double delta, double beta)
{
    MaterialItem *materialItem = dynamic_cast<MaterialItem *>(insertNewItem(Constants::MaterialType));
    materialItem->setItemName(name);

    RefractiveIndexItem *refractiveIndexItem =
            dynamic_cast<RefractiveIndexItem *>(materialItem->getItem(MaterialItem::P_REFRACTIVE_INDEX));
    Q_ASSERT(refractiveIndexItem);

    refractiveIndexItem->setDelta(delta);
    refractiveIndexItem->setBeta(beta);

    materialItem->setItemValue(MaterialItem::P_COLOR, MaterialUtils::suggestMaterialColorProperty(name).getVariant());

    return materialItem;
}

void MaterialModel::removeMaterial(MaterialItem *item)
{
    QModelIndex materialIndex = indexOfItem(item);
    removeRows(materialIndex.row(), 1, materialIndex.parent());
}

MaterialItem *MaterialModel::getMaterial(const QModelIndex &index)
{
    return dynamic_cast<MaterialItem *>(itemForIndex(index));
}

MaterialItem *MaterialModel::getMaterial(const MaterialProperty &property)
{
    qDebug() << "MaterialModel::getMaterial()";
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = index( i_row, 0, parentIndex );

         if (MaterialItem *material = dynamic_cast<MaterialItem *>(itemForIndex(itemIndex))){
             if(material->getIdentifier() == property.getIdentifier()) return material;
         }
    }
    return 0;
}

MaterialItem *MaterialModel::getMaterial(const QString &material_name)
{
    qDebug() << "MaterialModel::getMaterial()";
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = index( i_row, 0, parentIndex );

         if (MaterialItem *material = dynamic_cast<MaterialItem *>(itemForIndex(itemIndex))){
             if(material->itemName() == material_name) return material;
         }
    }
    return 0;
}

//! Returns clone of material with given index.

MaterialItem *MaterialModel::cloneMaterial(const QModelIndex &index)
{
    const MaterialItem *origMaterial = getMaterial(index);
    if(!origMaterial)
        return nullptr;

    SessionItem *clonedMaterial = copyParameterizedItem(origMaterial, 0);
    clonedMaterial->setItemValue(MaterialItem::P_IDENTIFIER, GUIHelpers::createUuid());
    clonedMaterial->setItemName(origMaterial->itemName()+" (clone)");
    return dynamic_cast<MaterialItem *>(clonedMaterial);
}
