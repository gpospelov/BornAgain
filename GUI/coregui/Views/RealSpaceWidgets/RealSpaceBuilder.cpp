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
                                const SceneGeometry& sceneGeometry,
                                const RealSpace::Camera::Position& cameraPosition)
{
    // default value of cameraPosition is in RealSpaceBuilder.h

    model->defCamPos = cameraPosition;

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

    // Checking if there is any rotation (transformation) of the particle

    RealSpace::Vector3D rotate;

    if(particleItem.getItem(ParticleItem::T_TRANSFORMATION))
        rotate = RealSpaceBuilderUtils::implementParticleRotation(particleItem);

    auto particle = TransformTo3D::createParticle(particleItem);

    if (particle) {
        SessionItem* positionItem = particleItem.getItem(ParticleItem::P_POSITION);
        float x = positionItem->getItemValue(VectorItem::P_X).toFloat();
        float y = positionItem->getItemValue(VectorItem::P_Y).toFloat();
        float z = positionItem->getItemValue(VectorItem::P_Z).toFloat();
        RealSpace::Vector3D position(x + origin.x(),y + origin.y(),z + origin.z());
        particle->transform(rotate, position);
        model->add(particle.release());
    }
}
