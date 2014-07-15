// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ItemFactory.cpp
//! @brief     Implements class ItemFactory.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ItemFactory.h"
#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "ParticleLayoutItem.h"
#include "ParticleItem.h"
#include "ParticleCoreShellItem.h"
#include "ParaCrystalItems.h"
#include "InstrumentItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include <QDebug>

namespace {
template<typename T> ParameterizedItem *createInstance() { return new T; }

ItemFactory::ItemMap_t initializeItemMap() {
    ItemFactory::ItemMap_t result;

    result[Constants::MultiLayerType] = &createInstance<MultiLayerItem>;
    result[Constants::LayerType] = &createInstance<LayerItem>;
    result[Constants::ParticleLayoutType] = &createInstance<ParticleLayoutItem>;
    result[Constants::ParticleType] = &createInstance<ParticleItem>;
    result[Constants::ParticleCoreShellType] = &createInstance<ParticleCoreShellItem>;
    result[Constants::InterferenceFunction1DParaCrystalType] = &createInstance<InterferenceFunction1DParaCrystalItem>;
    result[Constants::InterferenceFunction2DParaCrystalType] = &createInstance<InterferenceFunction2DParaCrystalItem>;
    result[Constants::InstrumentType] = &createInstance<InstrumentItem>;
    result[Constants::DetectorType] = &createInstance<DetectorItem>;
    result[Constants::BeamType] = &createInstance<BeamItem>;

    return result;
}
}

QStringList ItemFactory::m_valid_top_item_names = QStringList()
        << Constants::MultiLayerType
        << Constants::LayerType
        << Constants::ParticleLayoutType
        << Constants::ParticleType
        << Constants::ParticleCoreShellType
        << Constants::InterferenceFunction1DParaCrystalType
        << Constants::InterferenceFunction2DParaCrystalType;


ItemFactory::ItemMap_t ItemFactory::m_item_map = initializeItemMap();


ParameterizedItem *ItemFactory::createItem(const QString &model_name,
                                           ParameterizedItem *parent)
{
    if (model_name.isEmpty()) {
        return createEmptyItem();
    }

    if(!m_item_map.contains(model_name)) return 0;

    ParameterizedItem *result = m_item_map[model_name]();
    if(parent) {
        parent->insertChildItem(-1, result);
    }

    return result;
}


ParameterizedItem *ItemFactory::createEmptyItem()
{
    return new ParameterizedItem();
}


QList<QString> ItemFactory::getValidTopItemNames() {
    return m_valid_top_item_names;
}

