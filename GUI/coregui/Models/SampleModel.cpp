// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleModel.cpp
//! @brief     Implements class SampleModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SampleModel.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"

SampleModel::SampleModel(QObject *parent)
    : SessionModel(SessionXML::SampleModelTag, parent)
    , m_block_explore_for_material(false)
{
    setObjectName(SessionXML::SampleModelTag);
}

SampleModel *SampleModel::createCopy(SessionItem *parent)
{
    SampleModel *result = new SampleModel();
    result->initFrom(this, parent);
    return result;
}

MultiLayerItem *SampleModel::multiLayerItem(const QString &item_name)
{
    return dynamic_cast<MultiLayerItem *>(topItem(Constants::MultiLayerType, item_name));
}

void SampleModel::onMaterialModelChanged(const QModelIndex &, const QModelIndex &)
{
    if(m_block_explore_for_material)
        return;

    m_block_explore_for_material = true;
    exploreForMaterials();
    m_block_explore_for_material = false;
}

void SampleModel::exploreForMaterials(const QModelIndex &parentIndex)
{

    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);
        if (SessionItem *item = itemForIndex(itemIndex)) {
            if (item->modelType() == Constants::LayerType
                || item->modelType() == Constants::ParticleType) {
                // we pretend here that MaterialProperty changed to update IView colors
                item->getItem(LayerItem::P_MATERIAL)->emitDataChanged();
            }
        }
        exploreForMaterials(itemIndex);
    }
}
