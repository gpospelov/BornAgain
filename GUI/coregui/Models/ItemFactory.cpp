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
#include "ParaCrystalItems.h"
#include "InstrumentItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include <QDebug>

QList<QString> ItemFactory::m_all_item_names = QList<QString>()
        << QString("MultiLayer")
        << QString("Layer")
        << QString("ParticleLayout")
        << QString("Particle")
        << QString("InterferenceFunction1DParaCrystal")
        << QString("InterferenceFunction2DParaCrystal")
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
    if (model_name==QString("MultiLayer")) {
        return new MultiLayerItem(parent);
    }
    else if (model_name==QString("Layer")) {
        return new LayerItem(parent);
    }
    else if (model_name==QString("ParticleLayout")) {
        return new ParticleLayoutItem(parent);
    }
    else if (model_name==QString("Particle")) {
        return new ParticleItem(parent);
    }
    else if (model_name==QString("InterferenceFunction1DParaCrystal")) {
        return new InterferenceFunction1DParaCrystalItem(parent);
    }
    else if (model_name==QString("InterferenceFunction2DParaCrystal")) {
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
