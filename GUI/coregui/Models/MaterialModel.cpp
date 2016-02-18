// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaterialModel.cpp
//! @brief     Implements class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialModel.h"
#include "MaterialItem.h"
#include "RefractiveIndexItem.h"
#include "MaterialUtils.h"
#include "MaterialProperty.h"
#include <QDebug>

MaterialModel::MaterialModel(QObject *parent)
    : SessionModel(SessionXML::MaterialModelTag, parent)
{
    setObjectName(SessionXML::MaterialModelTag);
}

MaterialItem *MaterialModel::addMaterial(const QString &name, double delta, double beta)
{
    MaterialItem *materialItem = dynamic_cast<MaterialItem *>(insertNewItem(Constants::MaterialType));
    materialItem->setName(name);

    RefractiveIndexItem *refractiveIndexItem = dynamic_cast<RefractiveIndexItem *>(materialItem->getSubItems()[MaterialItem::P_REFRACTIVE_INDEX]);
    Q_ASSERT(refractiveIndexItem);

    refractiveIndexItem->setDelta(delta);
    refractiveIndexItem->setBeta(beta);

    materialItem->setRegisteredProperty(MaterialItem::P_COLOR, MaterialUtils::suggestMaterialColorProperty(name).getVariant());

    return materialItem;
}

void MaterialModel::removeMaterial(MaterialItem *item)
{
    QModelIndex materialIndex = indexOfItem(item);
    removeRows(materialIndex.row(), 1, materialIndex.parent());
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
             if(material->name() == material_name) return material;
         }
    }
    return 0;
}
