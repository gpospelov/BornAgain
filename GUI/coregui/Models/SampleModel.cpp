#include "SampleModel.h"
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "LayerItem.h"
#include "ParticleItem.h"
#include <QDebug>


SampleModel::SampleModel(QObject *parent)
    : SessionModel(SessionXML::SampleModelTag, parent)
{

}

SampleModel *SampleModel::createCopy(ParameterizedItem *parent)
{
    SampleModel *result = new SampleModel();
    result->initFrom(this, parent);
    return result;
}

void SampleModel::onMaterialModelChanged(const QModelIndex &first, const QModelIndex & /* second */)
{
    MaterialModel *materialModel = qobject_cast<MaterialModel *>(sender());

    qDebug() << "SampleModel::onMaterialModelChanged()" << first;

    Q_ASSERT(materialModel);

    MaterialItem *material = dynamic_cast<MaterialItem *>(materialModel->itemForIndex(first));
    Q_ASSERT(material);

    m_material_identifier = material->getIdentifier();

    exploreForMaterials();
}


void SampleModel::exploreForMaterials(const QModelIndex & parentIndex)
{

    qDebug() << "SampleModel::exploreForMaterials";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    for( int i_row = 0; i_row < rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = itemForIndex(itemIndex)){
             if(item->modelType() == Constants::LayerType || item->modelType() == Constants::ParticleType) {
                 qDebug() << " found item" << item->modelType();
                 MaterialProperty material_property = item->getRegisteredProperty(LayerItem::P_MATERIAL).value<MaterialProperty>();
                 if(material_property.getIdentifier() == m_material_identifier) {
                     item->setRegisteredProperty(LayerItem::P_MATERIAL, material_property.getVariant());
                 }

             }

         } else {
             qDebug() << "not a parameterized graphics item";
         }

         exploreForMaterials(itemIndex);
     }
}
