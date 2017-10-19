// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.cpp
//! @brief     Implements namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TransformTo3D.h"
#include "SessionItem.h"
#include "FormFactorItems.h"
#include "ParticleItem.h"
#include "MaterialProperty.h"
#include "VectorItem.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"

namespace {
    const double layer_size = 50.0;
    const double top_layer_thickness = 25.0;
    const double bottom_layer_thickness = 25.0;
    const double layer_min_thickness = 2.0;

    bool isTopLayer(const SessionItem& layerItem) {
        auto layers = layerItem.parent()->getItems(MultiLayerItem::T_LAYERS);
        return layers.indexOf(const_cast<SessionItem*>(&layerItem)) == 0;
    }

    bool isBottomLayer(const SessionItem& layerItem) {
        auto layers = layerItem.parent()->getItems(MultiLayerItem::T_LAYERS);
        return layers.indexOf(const_cast<SessionItem*>(&layerItem)) == layers.size() -1;
    }

}

double TransformTo3D::visualLayerThickness(const SessionItem& layerItem)
{
    Q_ASSERT(layerItem.modelType() == Constants::LayerType);

    double thickness(0.0);
    if(isTopLayer(layerItem))
        thickness = top_layer_thickness;
    else if(isBottomLayer(layerItem))
        thickness = bottom_layer_thickness;
    else
        thickness = layerItem.getItemValue(LayerItem::P_THICKNESS).toDouble();

    return thickness == 0.0 ? layer_min_thickness :  thickness;
}

std::unique_ptr<ba3d::Layer> TransformTo3D::createLayer(const SessionItem& layerItem, const QVector3D& origin)
{
    Q_ASSERT(layerItem.modelType() == Constants::LayerType);

    double thickness = TransformTo3D::visualLayerThickness(layerItem);

    double s2 = layer_size;
    double ztop = origin.z() + thickness;
    double zbottom = origin.z();

    std::unique_ptr<ba3d::Layer> result = std::make_unique<ba3d::Layer>(
        ba3d::dxyz(ba3d::dr(-s2,+s2), ba3d::dr(-s2,+s2), ba3d::dr(ztop, zbottom)));

    QColor color = layerItem.getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>().getColor();
    color.setAlphaF(.3);

    result->color = color;

    return result;
}


std::unique_ptr<ba3d::particle::Particle>
TransformTo3D::createParticle(const SessionItem& particleItem)
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    std::unique_ptr<ba3d::particle::Particle> result;

    auto ffItem = static_cast<FormFactorItem*>(
                particleItem.getGroupItem(ParticleItem::P_FORM_FACTOR));

    if(ffItem->modelType() == Constants::CylinderType) {
        double radius = ffItem->getItemValue(CylinderItem::P_RADIUS).toDouble();
        double height = ffItem->getItemValue(CylinderItem::P_HEIGHT).toDouble();
        result = std::make_unique<ba3d::particle::Cylinder>(radius, height);
    }

    else if(ffItem->modelType() == Constants::BoxType) {
        double length = ffItem->getItemValue(BoxItem::P_LENGTH).toDouble();
        double width = ffItem->getItemValue(BoxItem::P_WIDTH).toDouble();
        double height = ffItem->getItemValue(BoxItem::P_HEIGHT).toDouble();
        result = std::make_unique<ba3d::particle::Box>(length, width, height);
    }

    if(result) {

        MaterialProperty material
            = particleItem.getItemValue(ParticleItem::P_MATERIAL).value<MaterialProperty>();

        result->color = material.getColor();

        SessionItem* positionItem = particleItem.getItem(ParticleItem::P_POSITION);
        double x = positionItem->getItemValue(VectorItem::P_X).toDouble();
        double y = positionItem->getItemValue(VectorItem::P_Y).toDouble();
        double z = positionItem->getItemValue(VectorItem::P_Z).toDouble();
        result->transform(ba3d::xyz::_0, ba3d::xyz(x, y, z));
    }

    return result;
}
