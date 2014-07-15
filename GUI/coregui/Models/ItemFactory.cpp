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

QList<QString> ItemFactory::m_all_item_names = QList<QString>()
        << Constants::MultiLayerType
        << Constants::LayerType
        << Constants::ParticleLayoutType
        << Constants::ParticleType
        << Constants::ParticleCoreShellType
        << Constants::InterferenceFunction1DParaCrystalType
        << Constants::InterferenceFunction2DParaCrystalType
        << QString("Instrument")
        << QString("Detector")
        << QString("Beam");

ParameterizedItem *ItemFactory::createItem(const QString &model_name,
                                           ParameterizedItem *parent)
{
    //qDebug() << "ItemFactory::createItem() -> " << model_name << parent;
    if (model_name.isEmpty()) {
        return createEmptyItem();
    }
    if (!isValidName(model_name)) {
        return 0;
    }
    if (model_name==Constants::MultiLayerType) {
        return new MultiLayerItem(parent);
    }
    else if (model_name==Constants::LayerType) {
        return new LayerItem(parent);
    }
    else if (model_name==Constants::ParticleLayoutType) {
        return new ParticleLayoutItem(parent);
    }
    else if (model_name==Constants::ParticleType) {
        return new ParticleItem(parent);
    }
    else if (model_name==Constants::ParticleCoreShellType) {
        return new ParticleCoreShellItem(parent);
    }
    else if (model_name==Constants::InterferenceFunction1DParaCrystalType) {
        return new InterferenceFunction1DParaCrystalItem(parent);
    }
    else if (model_name==Constants::InterferenceFunction2DParaCrystalType) {
        return new InterferenceFunction2DParaCrystalItem(parent);
    }
    else if (model_name==QString("Instrument")) {
        return new InstrumentItem(parent);
    }
    else if (model_name==QString("Beam")) {
        return new BeamItem(parent);
    }
    else if (model_name==QString("Detector")) {
        return new DetectorItem(parent);
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

QList<QString> ItemFactory::getAllItemNames() {
    QList<QString> result = m_all_item_names;
    return result;
}

