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
#include "RealSpaceCanvas.h"

#include "ParticleComposition.h"
#include "ParticleCompositionItem.h"
#include "GUIDomainSampleVisitor.h"

#include "FormFactorAnisoPyramid.h"
#include "FormFactorBox.h"
#include "FormFactorCone.h"
#include "FormFactorCone6.h"
#include "FormFactorCuboctahedron.h"
#include "FormFactorCylinder.h"
#include "FormFactorDodecahedron.h"
#include "FormFactorEllipsoidalCylinder.h"
#include "FormFactorFullSphere.h"
#include "FormFactorFullSpheroid.h"
#include "FormFactorHemiEllipsoid.h"
#include "FormFactorIcosahedron.h"
#include "FormFactorPrism3.h"
#include "FormFactorPrism6.h"
#include "FormFactorPyramid.h"
#include "FormFactorTetrahedron.h"
#include "FormFactorTruncatedCube.h"
#include "FormFactorTruncatedSphere.h"
#include "FormFactorTruncatedSpheroid.h"

namespace {
    bool isTopLayer(const SessionItem& layerItem) {
        auto layers = layerItem.parent()->getItems(MultiLayerItem::T_LAYERS);
        return layers.indexOf(const_cast<SessionItem*>(&layerItem)) == 0;
    }
    bool isBottomLayer(const SessionItem& layerItem) {
        auto layers = layerItem.parent()->getItems(MultiLayerItem::T_LAYERS);
        return layers.indexOf(const_cast<SessionItem*>(&layerItem)) == layers.size() -1;
    }
}

double TransformTo3D::visualLayerThickness(
        const SessionItem& layerItem, const SceneGeometry& sceneGeometry)
{
    Q_ASSERT(layerItem.modelType() == Constants::LayerType);

    double thickness(0.0);
    if(isTopLayer(layerItem))
        thickness = sceneGeometry.layer_top_thickness();
    else if(isBottomLayer(layerItem))
        thickness = sceneGeometry.layer_bottom_thickness();
    else
        thickness = layerItem.getItemValue(LayerItem::P_THICKNESS).toDouble();

    return thickness == 0.0 ? sceneGeometry.layer_min_thickness() :  thickness;
}

std::unique_ptr<RealSpace::Layer> TransformTo3D::createLayer(
        const SessionItem& layerItem, const SceneGeometry &sceneGeometry, const QVector3D& origin)
{
    Q_ASSERT(layerItem.modelType() == Constants::LayerType);

    double thickness = TransformTo3D::visualLayerThickness(layerItem, sceneGeometry);

    double s2 = sceneGeometry.layer_size();
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
    }
    return result;
}

std::unique_ptr<RealSpace::Particles::Particle>
TransformTo3D::createParticleVersion2(const SessionItem &particleItem)
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    std::unique_ptr<RealSpace::Particles::Particle> result;

    auto ffItem = static_cast<FormFactorItem*>(
                particleItem.getGroupItem(ParticleItem::P_FORM_FACTOR));

    auto unique_ff = ffItem->createFormFactor();

    result = createParticlefromIFormFactor(unique_ff.get());

    // setting colour of the particle
    if(result) {
        ExternalProperty material
            = particleItem.getItemValue(ParticleItem::P_MATERIAL).value<ExternalProperty>();

        result->color = material.color();
    }
    return result;
}

std::unique_ptr<RealSpace::Particles::Particle>
TransformTo3D::createParticlefromIFormFactor(const IFormFactor* ff)
{
    std::unique_ptr<RealSpace::Particles::Particle> result;

    if(auto ff_AnisoPyramid = dynamic_cast<const FormFactorAnisoPyramid*>(ff)) {
        double length = ff_AnisoPyramid->getLength();
        double width = ff_AnisoPyramid->getWidth();
        double height = ff_AnisoPyramid->getHeight();
        double alpha = ff_AnisoPyramid->getAlpha();
        result = std::make_unique<RealSpace::Particles::AnisoPyramid>(length, width, height,
                                                                      alpha);
    }
    else if(auto ff_Box = dynamic_cast<const FormFactorBox*>(ff)) {
        double length = ff_Box->getLength();
        double width = ff_Box->getWidth();
        double height = ff_Box->getHeight();
        result = std::make_unique<RealSpace::Particles::Box>(length, width, height);
    }
    else if(auto ff_Cone = dynamic_cast<const FormFactorCone*>(ff)) {
        double radius = ff_Cone->getRadius();
        double height = ff_Cone->getHeight();
        double alpha = ff_Cone->getAlpha();
        result = std::make_unique<RealSpace::Particles::Cone>(radius, height, alpha);
    }
    else if(auto ff_Cone6 = dynamic_cast<const FormFactorCone6*>(ff)) {
        double baseedge = ff_Cone6->getBaseEdge();
        double height = ff_Cone6->getHeight();
        double alpha = ff_Cone6->getAlpha();
        result = std::make_unique<RealSpace::Particles::Cone6>(baseedge, height, alpha);
    }
    else if(auto ff_Cuboctahedron = dynamic_cast<const FormFactorCuboctahedron*>(ff)) {
        double length = ff_Cuboctahedron->getLength();
        double height = ff_Cuboctahedron->getHeight();
        double height_ratio = ff_Cuboctahedron->getHeightRatio();
        double alpha = ff_Cuboctahedron->getAlpha();
        result = std::make_unique<RealSpace::Particles::Cuboctahedron>(length, height,
                                                                       height_ratio, alpha);
    }
    else if(auto ff_Cylinder = dynamic_cast<const FormFactorCylinder*>(ff)) {
        double radius = ff_Cylinder->getRadius();
        double height = ff_Cylinder->getHeight();
        result = std::make_unique<RealSpace::Particles::Cylinder>(radius, height);
    }
    else if(auto ff_Dodecahedron = dynamic_cast<const FormFactorDodecahedron*>(ff)) {
        double edge = ff_Dodecahedron->getEdge();
        result = std::make_unique<RealSpace::Particles::Dodecahedron>(edge);
    }
    else if(auto ff_EllipsoidalCylinder = dynamic_cast<const FormFactorEllipsoidalCylinder*>(ff)) {
        double radius_x = ff_EllipsoidalCylinder->getRadiusX();
        double radius_y = ff_EllipsoidalCylinder->getRadiusY();
        double height = ff_EllipsoidalCylinder->getHeight();
        result = std::make_unique<RealSpace::Particles::EllipsoidalCylinder>(radius_x, radius_y,
                                                                             height);
    }
    else if(auto ff_FullSphere = dynamic_cast<const FormFactorFullSphere*>(ff)) {
        double radius = ff_FullSphere->getRadius();
        result = std::make_unique<RealSpace::Particles::FullSphere>(radius);
    }

    else if(auto ff_FullSpheroid = dynamic_cast<const FormFactorFullSpheroid*>(ff)) {
        double radius = ff_FullSpheroid->getRadius();
        double height = ff_FullSpheroid->getHeight();
        result = std::make_unique<RealSpace::Particles::FullSpheroid>(radius, height);
    }
    else if(auto ff_HemiEllipsoid = dynamic_cast<const FormFactorHemiEllipsoid*>(ff)) {
        double radius_x = ff_HemiEllipsoid->getRadiusX();
        double radius_y = ff_HemiEllipsoid->getRadiusY();
        double height = ff_HemiEllipsoid->getHeight();
        result = std::make_unique<RealSpace::Particles::HemiEllipsoid>(radius_x, radius_y,
                                                                             height);
    }
    else if(auto ff_Icosahedron = dynamic_cast<const FormFactorIcosahedron*>(ff)) {
        double edge = ff_Icosahedron->getEdge();
        result = std::make_unique<RealSpace::Particles::Icosahedron>(edge);
    }

    else if(auto ff_Prism3 = dynamic_cast<const FormFactorPrism3*>(ff)) {
        double baseedge = ff_Prism3->getBaseEdge();
        double height = ff_Prism3->getHeight();
        result = std::make_unique<RealSpace::Particles::Prism3>(baseedge, height);
    }
    else if(auto ff_Prism6 = dynamic_cast<const FormFactorPrism6*>(ff)) {
        double baseedge = ff_Prism6->getBaseEdge();
        double height = ff_Prism6->getHeight();
        result = std::make_unique<RealSpace::Particles::Prism6>(baseedge, height);
    }
    else if(auto ff_Pyramid = dynamic_cast<const FormFactorPyramid*>(ff)) {
        double baseedge = ff_Pyramid->getBaseEdge();
        double height = ff_Pyramid->getHeight();
        double alpha = ff_Pyramid->getAlpha();
        result = std::make_unique<RealSpace::Particles::Pyramid>(baseedge, height, alpha);
    }
    else if(auto ff_Tetrahedron = dynamic_cast<const FormFactorTetrahedron*>(ff)) {
        double baseedge = ff_Tetrahedron->getBaseEdge();
        double height = ff_Tetrahedron->getHeight();
        double alpha = ff_Tetrahedron->getAlpha();
        result = std::make_unique<RealSpace::Particles::Tetrahedron>(baseedge, height, alpha);
    }
    else if(auto ff_TruncatedCube = dynamic_cast<const FormFactorTruncatedCube*>(ff)) {
        double length = ff_TruncatedCube->getLength();
        double removed_length = ff_TruncatedCube->getRemovedLength();
        result = std::make_unique<RealSpace::Particles::TruncatedCube>(length, removed_length);
    }
    else if(auto ff_TruncatedSphere = dynamic_cast<const FormFactorTruncatedSphere*>(ff)) {
        double radius = ff_TruncatedSphere->getRadius();
        double height = ff_TruncatedSphere->getHeight();
        //double removed_top = ff_TruncatedSphere->getRemovedTop();
        result = std::make_unique<RealSpace::Particles::TruncatedSphere>(radius, height);
    }
    else if(auto ff_TruncatedSpheroid = dynamic_cast<const FormFactorTruncatedSpheroid*>(ff)) {
        double radius = ff_TruncatedSpheroid->getRadius();
        double height = ff_TruncatedSpheroid->getHeight();
        double hfc = ff_TruncatedSpheroid->getHeightFlattening();
        //double removed_top = ff_TruncatedSpheroid->getRemovedTop();
        result = std::make_unique<RealSpace::Particles::TruncatedSpheroid>(radius, height, hfc);
    }

    return result;
}
