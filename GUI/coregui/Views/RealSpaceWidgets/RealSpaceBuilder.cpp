// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.cpp
//! @brief     Implements class RealSpaceBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "RealSpaceCanvas.h"
#include "SessionItem.h"
#include "RealSpaceBuilderUtils.h"
#include "LayerItem.h"
#include "ExternalProperty.h"
#include "MultiLayerItem.h"
#include "TransformTo3D.h"
#include "ParticleLayoutItem.h"
#include <ba3d/model/layer.h>
#include <QDebug>

#include "ParticleItem.h"
#include "VectorItem.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include "Units.h"

RealSpaceBuilder::RealSpaceBuilder(QWidget* parent)
    : QWidget(parent)
{

}

RealSpaceBuilder::~RealSpaceBuilder()
{

}

void RealSpaceBuilder::populate(RealSpaceModel* model, const SessionItem& item,
                                const SceneGeometry& sceneGeometry)
{
    model->defCamPos = RealSpace::Camera::Position(
        RealSpace::Vector3D(0, -140, 90),   // eye
        RealSpace::Vector3D(0, 0, 0),       // center
        RealSpace::Vector3D::_z);             // up vector

    if (item.modelType() == Constants::MultiLayerType)
        populateMultiLayer(model, item, sceneGeometry);

    else if (item.modelType() == Constants::LayerType)
        populateLayer(model, item, sceneGeometry);

    else if (item.modelType() == Constants::ParticleLayoutType)
        populateLayout(model, item, sceneGeometry);

    else if (item.modelType() == Constants::ParticleType)
        populateParticle(model, item);
}

void RealSpaceBuilder::populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                          const SceneGeometry& sceneGeometry, const QVector3D&)
{
    double total_height(0.0);
    int index(0);
    for (auto layer : item.getItems(MultiLayerItem::T_LAYERS)) {

        if(index != 0)
            total_height += TransformTo3D::visualLayerThickness(*layer, sceneGeometry);

        populateLayer(model, *layer, sceneGeometry, QVector3D(0, 0, static_cast<float>(-total_height)));
        ++index;
    }

}

void RealSpaceBuilder::populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                     const SceneGeometry& sceneGeometry, const QVector3D& origin)
{
    auto layer = TransformTo3D::createLayer(layerItem, sceneGeometry, origin);
    model->addBlend(layer.release());

    for (auto layout : layerItem.getItems(LayerItem::T_LAYOUTS))
        populateLayout(model, *layout, sceneGeometry, origin);
}

void RealSpaceBuilder::populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                      const SceneGeometry& sceneGeometry, const QVector3D& origin)
{
    Q_ASSERT(layoutItem.modelType() == Constants::ParticleLayoutType);

    Q_UNUSED(origin);

    // If there is any interference function
    if (layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE))
        populateInterference(model, layoutItem, sceneGeometry);
    else
        RealSpaceBuilderUtils::populateRandomDistribution(model, layoutItem, sceneGeometry, this);
}

void RealSpaceBuilder::populateInterference(RealSpaceModel* model, const SessionItem& layoutItem,
                                            const SceneGeometry& sceneGeometry)
{
    // If there is no particle to populate
    if(!layoutItem.getItem(ParticleLayoutItem::T_PARTICLES))
        return;

    auto interference = layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE);

    // If interference type is 2D Lattice
    if (interference->modelType() == Constants::InterferenceFunction2DLatticeType)
        RealSpaceBuilderUtils::populateInterference2DLatticeType(model, layoutItem,
                                                                 sceneGeometry, this);

    /*

    // If interference type is 1D Lattice
    else if (interference->modelType() == Constants::InterferenceFunction1DLatticeType)
    {
        QMessageBox box;
        box.setText(interference->displayName());
        box.exec();
    }

    // If interference type is 2D ParaCrystal
    else if (interference->modelType() == Constants::InterferenceFunction2DParaCrystalType)
    {
    }

    // If interference type is Radial ParaCrystal
    else if (interference->modelType() == Constants::InterferenceFunctionRadialParaCrystalType)
    {
    }

    */
}

void RealSpaceBuilder::populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                                        const QVector3D& origin) const
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    // For checking if there is any rotation (transformation) of the particle

    RealSpace::Vector3D rotate;

    if(particleItem.getItem(ParticleItem::T_TRANSFORMATION))
    {
        rotate = RealSpaceBuilderUtils::implementRotation(particleItem);

        /*
        auto transformationItem = particleItem.getItem(ParticleItem::T_TRANSFORMATION);

        auto rotItem = transformationItem->getGroupItem(TransformationItem::P_ROT);

        // Same function as the one above
        //auto rotItem = static_cast<TransformationItem*>(transformationItem->getGroupItem(TransformationItem::P_ROT));

        if(rotItem->modelType() == Constants::ZRotationType)
        {
            auto ZRotItem = static_cast<ZRotationItem*>(rotItem);
            ZRotAngle = ZRotItem->getItemValue(ZRotationItem::P_ANGLE).toFloat();
        }
        else if(rotItem->modelType() == Constants::YRotationType)
        {
            auto YRotItem = static_cast<YRotationItem*>(rotItem);
            YRotAngle = YRotItem->getItemValue(YRotationItem::P_ANGLE).toFloat();
        }
        else if(rotItem->modelType() == Constants::XRotationType)
        {
            auto XRotItem = static_cast<XRotationItem*>(rotItem);
            XRotAngle = XRotItem->getItemValue(XRotationItem::P_ANGLE).toFloat();
        }
        else if(rotItem->modelType() == Constants::EulerRotationType)
        {
            auto EulerRotItem = static_cast<EulerRotationItem*>(rotItem);
            XRotAngle = EulerRotItem->getItemValue(EulerRotationItem::P_ALPHA).toFloat();
            YRotAngle = EulerRotItem->getItemValue(EulerRotationItem::P_BETA).toFloat();
            ZRotAngle = EulerRotItem->getItemValue(EulerRotationItem::P_GAMMA).toFloat();
        }
        else
        {
        }
        */
    }

    auto particle = TransformTo3D::createParticle(particleItem);

    if (particle) {
        particle->transform(rotate, RealSpace::Vector3D(origin.x(), origin.y(), origin.z()));
        model->add(particle.release());
    }
}
