// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.cpp
//! @brief     Implements namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TransformTo3D.h"
#include "SessionItem.h"
#include "FormFactorItems.h"
#include "ParticleItem.h"
#include "ExternalProperty.h"
#include "VectorItem.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "Units.h"

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

std::unique_ptr<RealSpace::Layer> TransformTo3D::createLayer(const SessionItem& layerItem, const QVector3D& origin)
{
    Q_ASSERT(layerItem.modelType() == Constants::LayerType);

    double thickness = TransformTo3D::visualLayerThickness(layerItem);

    double s2 = layer_size;
    double ztop = static_cast<double>(origin.z()) + thickness;
    double zbottom = static_cast<double>(origin.z());

    std::unique_ptr<RealSpace::Layer> result = std::make_unique<RealSpace::Layer>(
        RealSpace::VectorRange(RealSpace::Range(static_cast<float>(-s2),static_cast<float>(+s2)),
                               RealSpace::Range(static_cast<float>(-s2),static_cast<float>(+s2)),
                               RealSpace::Range(static_cast<float>(ztop),static_cast<float>(zbottom))));

    QColor color = layerItem.getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>().color();
    color.setAlphaF(.3);

    result->color = color;

    return result;
}


std::unique_ptr<RealSpace::Particles::Particle>
TransformTo3D::createParticle(const SessionItem& particleItem)
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    std::unique_ptr<RealSpace::Particles::Particle> result;

    auto ffItem = static_cast<FormFactorItem*>(
                particleItem.getGroupItem(ParticleItem::P_FORM_FACTOR));

    if(ffItem->modelType() == Constants::AnisoPyramidType) {
        double length = ffItem->getItemValue(AnisoPyramidItem::P_LENGTH).toDouble();
        double width = ffItem->getItemValue(AnisoPyramidItem::P_WIDTH).toDouble();
        double height = ffItem->getItemValue(AnisoPyramidItem::P_HEIGHT).toDouble();
        double alpha = ffItem->getItemValue(AnisoPyramidItem::P_ALPHA).toDouble();
        result = std::make_unique<RealSpace::Particles::AnisoPyramid>(length, width, height,
                                                                      Units::deg2rad(alpha));
    }

    else if(ffItem->modelType() == Constants::BoxType) {
        double length = ffItem->getItemValue(BoxItem::P_LENGTH).toDouble();
        double width = ffItem->getItemValue(BoxItem::P_WIDTH).toDouble();
        double height = ffItem->getItemValue(BoxItem::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::Box>(length, width, height);
    }

    else if(ffItem->modelType() == Constants::ConeType) {
        double radius = ffItem->getItemValue(ConeItem::P_RADIUS).toDouble();
        double height = ffItem->getItemValue(ConeItem::P_HEIGHT).toDouble();
        double alpha = ffItem->getItemValue(ConeItem::P_ALPHA).toDouble();
        result = std::make_unique<RealSpace::Particles::Cone>(radius, height,
                                                              Units::deg2rad(alpha));
    }

    else if(ffItem->modelType() == Constants::Cone6Type) {
        double baseedge = ffItem->getItemValue(Cone6Item::P_BASEEDGE).toDouble();
        double height = ffItem->getItemValue(Cone6Item::P_HEIGHT).toDouble();
        double alpha = ffItem->getItemValue(Cone6Item::P_ALPHA).toDouble();
        result = std::make_unique<RealSpace::Particles::Cone6>(baseedge, height,
                                                               Units::deg2rad(alpha));
    }

    else if(ffItem->modelType() == Constants::CuboctahedronType) {
        double length = ffItem->getItemValue(CuboctahedronItem::P_LENGTH).toDouble();
        double height = ffItem->getItemValue(CuboctahedronItem::P_HEIGHT).toDouble();
        double height_ratio = ffItem->getItemValue(CuboctahedronItem::P_HEIGHT_RATIO).toDouble();
        double alpha = ffItem->getItemValue(CuboctahedronItem::P_ALPHA).toDouble();
        result = std::make_unique<RealSpace::Particles::Cuboctahedron>(length, height,
                                                                       height_ratio,
                                                                       Units::deg2rad(alpha));
    }

    else if(ffItem->modelType() == Constants::CylinderType) {
        double radius = ffItem->getItemValue(CylinderItem::P_RADIUS).toDouble();
        double height = ffItem->getItemValue(CylinderItem::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::Cylinder>(radius, height);
    }

    else if(ffItem->modelType() == Constants::DodecahedronType) {
        double edge = ffItem->getItemValue(DodecahedronItem::P_EDGE).toDouble();
        result = std::make_unique<RealSpace::Particles::Dodecahedron>(edge);
    }

    else if(ffItem->modelType() == Constants::EllipsoidalCylinderType) {
        double radius_x = ffItem->getItemValue(EllipsoidalCylinderItem::P_RADIUS_X).toDouble();
        double radius_y = ffItem->getItemValue(EllipsoidalCylinderItem::P_RADIUS_Y).toDouble();
        double height = ffItem->getItemValue(EllipsoidalCylinderItem::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::EllipsoidalCylinder>(radius_x, radius_y,
                                                                             height);
    }

    else if(ffItem->modelType() == Constants::FullSphereType) {
        double radius = ffItem->getItemValue(FullSphereItem::P_RADIUS).toDouble();
        result = std::make_unique<RealSpace::Particles::FullSphere>(radius);
    }

    else if(ffItem->modelType() == Constants::FullSpheroidType) {
        double radius = ffItem->getItemValue(FullSpheroidItem::P_RADIUS).toDouble();
        double height = ffItem->getItemValue(FullSpheroidItem::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::FullSpheroid>(radius, height);
    }

    else if(ffItem->modelType() == Constants::HemiEllipsoidType) {
        double radius_x = ffItem->getItemValue(HemiEllipsoidItem::P_RADIUS_X).toDouble();
        double radius_y = ffItem->getItemValue(HemiEllipsoidItem::P_RADIUS_Y).toDouble();
        double height = ffItem->getItemValue(HemiEllipsoidItem::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::HemiEllipsoid>(radius_x, radius_y,
                                                                             height);
    }

    else if(ffItem->modelType() == Constants::IcosahedronType) {
        double edge = ffItem->getItemValue(IcosahedronItem::P_EDGE).toDouble();
        result = std::make_unique<RealSpace::Particles::Icosahedron>(edge);
    }

    else if(ffItem->modelType() == Constants::Prism3Type) {
        double baseedge = ffItem->getItemValue(Prism3Item::P_BASEEDGE).toDouble();
        double height = ffItem->getItemValue(Prism3Item::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::Prism3>(baseedge, height);
    }

    else if(ffItem->modelType() == Constants::Prism6Type) {
        double baseedge = ffItem->getItemValue(Prism6Item::P_BASEEDGE).toDouble();
        double height = ffItem->getItemValue(Prism6Item::P_HEIGHT).toDouble();
        result = std::make_unique<RealSpace::Particles::Prism6>(baseedge, height);
    }

    else if(ffItem->modelType() == Constants::PyramidType) {
        double baseedge = ffItem->getItemValue(PyramidItem::P_BASEEDGE).toDouble();
        double height = ffItem->getItemValue(PyramidItem::P_HEIGHT).toDouble();
        double alpha = ffItem->getItemValue(PyramidItem::P_ALPHA).toDouble();
        result = std::make_unique<RealSpace::Particles::Pyramid>(baseedge, height,
                                                                 Units::deg2rad(alpha));
    }

    else if(ffItem->modelType() == Constants::TetrahedronType) {
        double baseedge = ffItem->getItemValue(TetrahedronItem::P_BASEEDGE).toDouble();
        double height = ffItem->getItemValue(TetrahedronItem::P_HEIGHT).toDouble();
        double alpha = ffItem->getItemValue(TetrahedronItem::P_ALPHA).toDouble();
        result = std::make_unique<RealSpace::Particles::Tetrahedron>(baseedge, height,
                                                                     Units::deg2rad(alpha));
    }

    else if(ffItem->modelType() == Constants::TruncatedCubeType) {
        double length = ffItem->getItemValue(TruncatedCubeItem::P_LENGTH).toDouble();
        double removed_length = ffItem->getItemValue(TruncatedCubeItem::P_REMOVED_LENGTH).toDouble();
        result = std::make_unique<RealSpace::Particles::TruncatedCube>(length, removed_length);
    }

    else if(ffItem->modelType() == Constants::TruncatedSphereType) {
        double radius = ffItem->getItemValue(TruncatedSphereItem::P_RADIUS).toDouble();
        double height = ffItem->getItemValue(TruncatedSphereItem::P_HEIGHT).toDouble();
        //double removed_top = ffItem->getItemValue(TruncatedSphereItem::P_REMOVED_TOP).toDouble();
        result = std::make_unique<RealSpace::Particles::TruncatedSphere>(radius, height);
    }

    else if(ffItem->modelType() == Constants::TruncatedSpheroidType) {
        double radius = ffItem->getItemValue(TruncatedSpheroidItem::P_RADIUS).toDouble();
        double height = ffItem->getItemValue(TruncatedSpheroidItem::P_HEIGHT).toDouble();
        double hfc = ffItem->getItemValue(TruncatedSpheroidItem::P_HFC).toDouble();
        //double removed_top = ffItem->getItemValue(TruncatedSpheroidItem::P_REMOVED_TOP).toDouble();
        result = std::make_unique<RealSpace::Particles::TruncatedSpheroid>(radius, height, hfc);
    }

    if(result) {

        ExternalProperty material
            = particleItem.getItemValue(ParticleItem::P_MATERIAL).value<ExternalProperty>();

        result->color = material.color();

        SessionItem* positionItem = particleItem.getItem(ParticleItem::P_POSITION);
        double x = positionItem->getItemValue(VectorItem::P_X).toDouble();
        double y = positionItem->getItemValue(VectorItem::P_Y).toDouble();
        double z = positionItem->getItemValue(VectorItem::P_Z).toDouble();
        result->transform(RealSpace::Vector3D::_0, RealSpace::Vector3D(static_cast<float>(x),
                                                                       static_cast<float>(y),
                                                                       static_cast<float>(z)) );
    }

    return result;
}
