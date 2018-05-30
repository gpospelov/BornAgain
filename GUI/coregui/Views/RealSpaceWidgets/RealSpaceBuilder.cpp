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
#include "Particle.h"

#include "ParticleCoreShellItem.h"
#include "ParticleCoreShell.h"

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

    else if (item.modelType() == Constants::ParticleCoreShellType)
        populateParticle(model, item);

    else if (item.modelType() == Constants::ParticleCompositionType)
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
    if (layer)
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
    // if particle core shell is present
    if( particleItem.modelType() == Constants::ParticleCoreShellType)
    {
        auto particleCoreShellItem = dynamic_cast<const ParticleCoreShellItem*>(&particleItem);
        auto particleCoreShell = particleCoreShellItem->createParticleCoreShell();
        populateParticleCoreShell(model, particleCoreShell->coreParticle(),
                                  particleCoreShell->shellParticle(), origin);
    }

    // if particle composition is present
    else if(particleItem.modelType() == Constants::ParticleCompositionType)
    {
        auto particleCompositionItem = dynamic_cast<const ParticleCompositionItem*>(&particleItem);
        auto particleComposition = particleCompositionItem->createParticleComposition();
        populateParticleComposition(model, particleComposition.get(), origin);
    }

    else if(particleItem.modelType() == Constants::ParticleType)
    {
        auto pItem = dynamic_cast<const ParticleItem*>(&particleItem);
        auto particle = pItem->createParticle();
        auto particle3D = TransformTo3D::createParticle3D(particleItem);

        RealSpaceBuilderUtils::applyParticleTransformations(particle.get(), particle3D.get(),
                                                            origin);
        RealSpaceBuilderUtils::applyParticleColor(particle.get(), particle3D.get());

        if (particle3D)
            model->add(particle3D.release());
    }
}

void RealSpaceBuilder::populateParticleComposition(RealSpaceModel *model,
                                                   const ParticleComposition *particleComposition,
                                                   const QVector3D &origin) const
{
    SafePointerVector<IParticle> pc_vector = particleComposition->decompose();

    for (IParticle* pc_particle : pc_vector)
    {
        if(dynamic_cast<ParticleCoreShell*>(pc_particle))
        {
            auto particleCoreShell = dynamic_cast<ParticleCoreShell*>(pc_particle);
            populateParticleCoreShell(model, particleCoreShell->coreParticle(),
                                      particleCoreShell->shellParticle(), origin);
        }
        else
        {
            auto particle = dynamic_cast<Particle*>(pc_particle);
            const IFormFactor* ff = pc_particle->createFormFactor();

            // TRUE as long as ff is of IFormFactorDecorator (or its derived) type
            while(dynamic_cast<const IFormFactorDecorator*>(ff))
                ff = dynamic_cast<const IFormFactorDecorator*>(ff)->getFormFactor();

            auto particle3D = TransformTo3D::createParticlefromIFormFactor(ff);

            RealSpaceBuilderUtils::applyParticleTransformations(particle, particle3D.get(),
                                                                origin);
            RealSpaceBuilderUtils::applyParticleColor(particle, particle3D.get());

            if (particle3D)
                model->add(particle3D.release());
        }
    }
}

void RealSpaceBuilder::populateParticleCoreShell(RealSpaceModel *model,
                                                 const Particle *coreParticle, const Particle *shellParticle,
                                                 const QVector3D &origin) const
{
    const IFormFactor* coreParticleff = coreParticle->createFormFactor();
    const IFormFactor* shellParticleff = shellParticle->createFormFactor();

    // TRUE as long as coreParticleff is of IFormFactorDecorator (or its derived) type
    while(dynamic_cast<const IFormFactorDecorator*>(coreParticleff))
        coreParticleff =
                dynamic_cast<const IFormFactorDecorator*>(coreParticleff)->getFormFactor();

    // TRUE as long as shellParticleff is of IFormFactorDecorator (or its derived) type
    while(dynamic_cast<const IFormFactorDecorator*>(shellParticleff))
        shellParticleff =
                dynamic_cast<const IFormFactorDecorator*>(shellParticleff)->getFormFactor();

    auto coreParticle3D = TransformTo3D::createParticlefromIFormFactor(coreParticleff);
    auto shellParticle3D = TransformTo3D::createParticlefromIFormFactor(shellParticleff);

    // core particle
    RealSpaceBuilderUtils::applyParticleTransformations(coreParticle, coreParticle3D.get(), origin);
    RealSpaceBuilderUtils::applyParticleColor(coreParticle, coreParticle3D.get());

    // shell particle (set an alpha value of 0.5 for transparency)
    RealSpaceBuilderUtils::applyParticleTransformations(shellParticle, shellParticle3D.get(), origin);
    RealSpaceBuilderUtils::applyParticleColor(shellParticle, shellParticle3D.get(), 0.5);

    if (coreParticle3D)
        model->add(coreParticle3D.release());

    if (shellParticle3D)
        model->addBlend(shellParticle3D.release()); // use addBlend() for transparent object
}
