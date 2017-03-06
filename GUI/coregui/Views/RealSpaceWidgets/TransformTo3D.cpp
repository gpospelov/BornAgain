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
#include "GUIHelpers.h"

namespace {
    const double layer_alpha = 0.3;
    const double layer_size = 50;
    const double layer_min_thickness = 25;
}

std::unique_ptr<ba3d::Layer> TransformTo3D::createLayer(const SessionItem& layerItem, const QVector3D& origin)
{
    Q_ASSERT(layerItem.modelType() == Constants::LayerType);

    double thickness = layerItem.getItemValue(LayerItem::P_THICKNESS).toDouble();

    if(thickness == 0)
        thickness = layer_min_thickness;

    double s2 = layer_size;

//    double ztop = thickness;
//    double zbottom = 0.0;
    double ztop = origin.z() + thickness;
    double zbottom = origin.z();

    std::unique_ptr<ba3d::Layer> result = GUIHelpers::make_unique<ba3d::Layer>(
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
        result = GUIHelpers::make_unique<ba3d::particle::Cylinder>(radius, height);
    }

    else if(ffItem->modelType() == Constants::BoxType) {
        double length = ffItem->getItemValue(BoxItem::P_LENGTH).toDouble();
        double width = ffItem->getItemValue(BoxItem::P_WIDTH).toDouble();
        double height = ffItem->getItemValue(BoxItem::P_HEIGHT).toDouble();
        result = GUIHelpers::make_unique<ba3d::particle::Box>(length, width, height);
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
