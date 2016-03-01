// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SampleModel.cpp
//! @brief     Implements class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleModel.h"
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "ParticleItem.h"
#include <QDebug>

SampleModel::SampleModel(QObject *parent) : SessionModel(SessionXML::SampleModelTag, parent)
{
    setObjectName(SessionXML::SampleModelTag);
}

SampleModel *SampleModel::createCopy(ParameterizedItem *parent)
{
    SampleModel *result = new SampleModel();
    result->initFrom(this, parent);
    return result;
}

//! returns list of MultiLayers defined in the model
QMap<QString, ParameterizedItem *> SampleModel::getSampleMap() const
{
    return getTopItemMap(Constants::MultiLayerType);
}

MultiLayerItem *SampleModel::getMultiLayerItem(const QString &item_name)
{
    return dynamic_cast<MultiLayerItem *>(getTopItem(Constants::MultiLayerType, item_name));
}

void SampleModel::onMaterialModelChanged(const QModelIndex &first, const QModelIndex & /* second */)
{
    MaterialModel *materialModel = qobject_cast<MaterialModel *>(sender());
    qDebug() << "SampleModel::onMaterialModelChanged()" << first;
    Q_ASSERT(materialModel);
    MaterialItem *material = dynamic_cast<MaterialItem *>(materialModel->itemForIndex(first));
    if (!material)
        return;
    Q_ASSERT(material);
    m_material_identifier = material->getIdentifier();

    exploreForMaterials();
}

void SampleModel::exploreForMaterials(const QModelIndex &parentIndex)
{
    if (!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);
        if (ParameterizedItem *item = itemForIndex(itemIndex)) {
            if (item->modelType() == Constants::LayerType
                || item->modelType() == Constants::ParticleType) {
                qDebug() << " found item" << item->modelType();
                MaterialProperty material_property
                    = item->getRegisteredProperty(LayerItem::P_MATERIAL).value<MaterialProperty>();
                if (material_property.getIdentifier() == m_material_identifier) {
//                    item->setRegisteredProperty(LayerItem::P_MATERIAL,
//                                                material_property.getVariant());
                    // MaterialProperty of the layer corresponds to the material which just has been changed
                    // To trigger color change in ILayerView we have to trigger propertyChanged
                    //emit item->propertyChanged();
                    item->getPropertyItem(LayerItem::P_MATERIAL)->emitValueChanged();
                }
            }
        } else {
            qDebug() << "not a parameterized graphics item";
        }

        exploreForMaterials(itemIndex);
    }
}
