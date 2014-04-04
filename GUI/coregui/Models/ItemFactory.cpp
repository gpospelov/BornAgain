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

QList<QString> ItemFactory::m_all_item_names = QList<QString>()
        << QString("MultiLayer")
        << QString("Layer")
        << QString("ParticleLayout");

ParameterizedItem *ItemFactory::createItem(const QString &model_name,
                                           ParameterizedItem *parent)
{
    if (model_name.isEmpty()) {
        return createEmptyItem();
    }
    if (!m_all_item_names.contains(model_name)) {
        return 0;
    }
    if (model_name==QString("MultiLayer")) {
        return new MultiLayerItem(parent);
    }
    if (model_name==QString("Layer")) {
        return new LayerItem(parent);
    }
    if (model_name==QString("ParticleLayout")) {
        return new ParticleLayoutItem(parent);
    }
    return 0;
}

ParameterizedItem *ItemFactory::createEmptyItem()
{
    return new ParameterizedItem();
}


bool ItemFactory::isValidName(const QString &name)
{
    return m_all_item_names.contains(name);
}
