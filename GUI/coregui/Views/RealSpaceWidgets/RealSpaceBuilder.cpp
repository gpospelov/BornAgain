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

#include "ParticleCompositionItem.h"
#include "IParticle.h"
#include "IFormFactorDecorator.h"
#include "Rotations.h"
#include "Particle.h"
#include "Material.h"

#include <AppSvc.h>
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "MaterialItemUtils.h"

RealSpaceBuilder::RealSpaceBuilder(QWidget* parent)
    : QWidget(parent)
{

}

RealSpaceBuilder::~RealSpaceBuilder()
{

}

void RealSpaceBuilder::populate(RealSpaceModel* model,
                                const SessionItem& item,
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

void RealSpaceBuilder::populateMultiLayer(RealSpaceModel* model,
                                          const SessionItem& item,
                                          const SceneGeometry& sceneGeometry,
                                          const QVector3D&)
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

void RealSpaceBuilder::populateLayer(RealSpaceModel* model,
                                     const SessionItem& layerItem,
                                     const SceneGeometry& sceneGeometry,
                                     const QVector3D& origin)
{
    auto layer = TransformTo3D::createLayer(layerItem, sceneGeometry, origin);
    model->addBlend(layer.release());

    for (auto layout : layerItem.getItems(LayerItem::T_LAYOUTS))
        populateLayout(model, *layout, sceneGeometry, origin);
}

void RealSpaceBuilder::populateLayout(RealSpaceModel* model,
                                      const SessionItem& layoutItem,
                                      const SceneGeometry& sceneGeometry,
                                      const QVector3D& origin)
{
    Q_ASSERT(layoutItem.modelType() == Constants::ParticleLayoutType);

    Q_UNUSED(origin);

    // If there is any interference function
    if (layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE))
        populateInterference(model, layoutItem, sceneGeometry);
    else
        RealSpaceBuilderUtils::populateRandomDistribution(model, layoutItem, sceneGeometry, this);
}

void RealSpaceBuilder::populateInterference(RealSpaceModel* model,
                                            const SessionItem& layoutItem,
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

void RealSpaceBuilder::populateParticle(RealSpaceModel* model,
                                        const SessionItem& particleItem,
                                        const QVector3D& origin) const
{

    // if particle composition is present
    if(particleItem.modelType() == Constants::ParticleCompositionType)
    {
        const ParticleCompositionItem* particleCompositionItem =
                dynamic_cast<const ParticleCompositionItem*>(&particleItem);

        std::unique_ptr<ParticleComposition> particleComposition =
                particleCompositionItem->createParticleComposition();

        // abbreviating ParticleComposition as pc
        SafePointerVector<IParticle> pc_vector = particleComposition->decompose();

        for (IParticle* pc_particle : pc_vector)
        {
            // abbreviating FormFactor as ff
            IFormFactor* ff = pc_particle->createFormFactor();

            // TRUE as long as ff is of IFormFactorDecorator (or its derived) type
            while(dynamic_cast<IFormFactorDecorator*>(ff))
                ff = dynamic_cast<IFormFactorDecorator*>(ff)->getFormFactor();

            auto particle = TransformTo3D::createParticlefromIFormFactor(ff);

            if (particle) {
                // position of the current particle within the particle composition
                float x = static_cast<float>(pc_particle->position().x());
                float y = static_cast<float>(pc_particle->position().y());
                float z = static_cast<float>(pc_particle->position().z());
                RealSpace::Vector3D position(x + origin.x(), y + origin.y(), z + origin.z());


                // rotation of the current particle within the particle composition
                RealSpace::Vector3D pc_particle_rotate;

                IRotation* rotation = nullptr;

                rotation = const_cast<IRotation*>(pc_particle->rotation());

                // Checking if there is any rotation of the particle within the composition
                if(rotation)
                    pc_particle_rotate =
                            RealSpaceBuilderUtils::implementParticleRotationfromIRotation(rotation);


                if(dynamic_cast<Particle*>(pc_particle))
                {
                    Material* pc_particle_material = const_cast<Material*>(
                                dynamic_cast<Particle*>(pc_particle)->material());

                    QString material_name = QString::fromStdString(pc_particle_material->getName());

                    auto materialItem = AppSvc::materialModel()->materialFromName(material_name);

                    //auto matmodel = AppSvc::materialModel()->createCopy();
                    //auto materialItem = matmodel->materialFromName(material_name);

                    particle->color = materialItem->color();

                }

                particle->transform(pc_particle_rotate, position);
                model->add(particle.release());
            }

        }
    }
    else
    {
        Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

        //auto particle = TransformTo3D::createParticle(particleItem);
        auto particle = TransformTo3D::createParticleVersion2(particleItem);

        RealSpace::Vector3D rotate;

        // Checking if there is any rotation (transformation) of the particle
        if(particleItem.getItem(ParticleItem::T_TRANSFORMATION))
            rotate = RealSpaceBuilderUtils::implementParticleRotation(particleItem);

        if (particle) {
            SessionItem* positionItem = particleItem.getItem(ParticleItem::P_POSITION);
            float x = positionItem->getItemValue(VectorItem::P_X).toFloat();
            float y = positionItem->getItemValue(VectorItem::P_Y).toFloat();
            float z = positionItem->getItemValue(VectorItem::P_Z).toFloat();
            RealSpace::Vector3D position(x + origin.x(), y + origin.y(), z + origin.z());

            particle->transform(rotate, position);
            model->add(particle.release());
        }
    }
}
