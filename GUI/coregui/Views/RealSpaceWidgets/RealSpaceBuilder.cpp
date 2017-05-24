// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.cpp
//! @brief     Implements RealSpaceBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "SessionItem.h"
#include "LayerItem.h"
#include "MaterialProperty.h"
#include "MultiLayerItem.h"
#include "TransformTo3D.h"
#include "ParticleLayoutItem.h"
#include <ba3d/model/layer.h>
#include <QDebug>

namespace
{
const double layer_min_thickness = 25;
}

void RealSpaceBuilder::populate(RealSpaceModel* model, const SessionItem& item)
{
    model->defCamPos = ba3d::Camera::pos_t(
        ba3d::xyz(-10, -140, 20),   // eye
        ba3d::xyz(0, 0, -30),       // center
        ba3d::xyz::_z);             // up vector

    if (item.modelType() == Constants::MultiLayerType)
        populateMultiLayer(model, item);

    else if (item.modelType() == Constants::LayerType)
        populateLayer(model, item);

    else if (item.modelType() == Constants::ParticleLayoutType)
        populateLayout(model, item);

    else if (item.modelType() == Constants::ParticleType)
        populateParticle(model, item);
}

void RealSpaceBuilder::populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                          const QVector3D&)
{
    double total_height(0.0);
    int index(0);
    for (auto layer : item.getItems(MultiLayerItem::T_LAYERS)) {

        if(index != 0)
            total_height += TransformTo3D::visualLayerThickness(*layer);

        populateLayer(model, *layer, QVector3D(0, 0, -total_height));
        ++index;
    }

}

void RealSpaceBuilder::populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                     const QVector3D& origin)
{
    auto layer = TransformTo3D::createLayer(layerItem, origin);
    model->addBlend(layer.release());

    for (auto layout : layerItem.getItems(LayerItem::T_LAYOUTS))
        populateLayout(model, *layout, origin);
}

void RealSpaceBuilder::populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                      const QVector3D& origin)
{
    Q_ASSERT(layoutItem.modelType() == Constants::ParticleLayoutType);

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
        populateParticle(model, *particle, origin);
}

void RealSpaceBuilder::populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                                        const QVector3D& origin)
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    auto particle = TransformTo3D::createParticle(particleItem);

    if (particle) {
        particle->transform(ba3d::xyz::_0, ba3d::xyz(origin.x(), origin.y(), origin.z()));
        model->add(particle.release());
    }
}
