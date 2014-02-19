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
#include "ParticleDecorationItem.h"


ParameterizedItem *ItemFactory::createItem(const QString &model_name)
{
    if (model_name==QString("MultiLayer")) {
        return new MultiLayerItem();
    }
    if (model_name==QString("Layer")) {
        return new LayerItem();
    }
    if (model_name==QString("ParticleDecoration")) {
        return new ParticleDecorationItem();
    }
    return 0;
}
