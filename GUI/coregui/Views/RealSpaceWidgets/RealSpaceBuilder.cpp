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
#include "ExternalProperty.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "Particle.h"
#include "Particle3DContainer.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShell.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "RealSpaceBuilderUtils.h"
#include "RealSpaceCanvas.h"
#include "RealSpaceModel.h"
#include "SessionItem.h"
#include "TransformTo3D.h"
#include "Units.h"
#include "VectorItem.h"
#include <QDebug>
#include <ba3d/model/layer.h>

RealSpaceBuilder::RealSpaceBuilder(QWidget* parent) : QWidget(parent)
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
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == Constants::ParticleCompositionType)
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == Constants::ParticleCoreShellType)
        populateParticleFromParticleItem(model, item);

    else if (item.modelType() == Constants::ParticleDistributionType)
        populateParticleFromParticleItem(model, item);
}

void RealSpaceBuilder::populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                          const SceneGeometry& sceneGeometry, const QVector3D&)
{
    double total_height(0.0);
    int index(0);
    for (auto layer : item.getItems(MultiLayerItem::T_LAYERS)) {

        if (index != 0)
            total_height += TransformTo3D::visualLayerThickness(*layer, sceneGeometry);

        populateLayer(model, *layer, sceneGeometry,
                      QVector3D(0, 0, static_cast<float>(-total_height)));
        ++index;
    }
}

void RealSpaceBuilder::populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                     const SceneGeometry& sceneGeometry, const QVector3D& origin)
{
    auto layer = TransformTo3D::createLayer(layerItem, sceneGeometry, origin);
    if (layer)
        model->addBlend(layer.release());

    for (auto layout : layerItem.getItems(LayerItem::T_LAYOUTS))
        populateLayout(model, *layout, sceneGeometry, origin);
}

void RealSpaceBuilder::populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                      const SceneGeometry& sceneGeometry, const QVector3D& origin)
{
    Q_ASSERT(layoutItem.modelType() == Constants::ParticleLayoutType);

    Q_UNUSED(origin);

    // If there is no particle to populate
    if (!layoutItem.getItem(ParticleLayoutItem::T_PARTICLES))
        return;

    auto particle3DContainer_vector = RealSpaceBuilderUtils::particle3DContainerVector(layoutItem);

    // If there is an interference function present
    if (layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE))
        populateInterference(model, layoutItem, particle3DContainer_vector, sceneGeometry);
    else {
        RealSpaceBuilderUtils::populateRandomDistribution(
            model, layoutItem, particle3DContainer_vector, sceneGeometry, this);
    }
}

void RealSpaceBuilder::populateInterference(
    RealSpaceModel* model, const SessionItem& layoutItem,
    std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry)
{
    // If there is no particle to populate
    if (!layoutItem.getItem(ParticleLayoutItem::T_PARTICLES))
        return;

    auto interferenceLattice = layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE);
    auto interferenceItem = dynamic_cast<const InterferenceFunctionItem*>(interferenceLattice);
    auto interference = interferenceItem->createInterferenceFunction();

    // If interference type is 2D Lattice
    if (interferenceLattice->modelType() == Constants::InterferenceFunction2DLatticeType)
        RealSpaceBuilderUtils::populateInterference2DLatticeType(
            interference.get(), model, particle3DContainer_vector, sceneGeometry, this);

    // If interference type is 1D Lattice
    else if (interferenceLattice->modelType() == Constants::InterferenceFunction1DLatticeType)
        RealSpaceBuilderUtils::populateInterference1DLatticeType(
            interference.get(), model, particle3DContainer_vector, sceneGeometry, this);

    /*
    // If interference type is 2D ParaCrystal
    else if (interferenceLattice->modelType() == Constants::InterferenceFunction2DParaCrystalType)
    {
    }

    // If interference type is Radial ParaCrystal
    else if (interferenceLattice->modelType() ==
    Constants::InterferenceFunctionRadialParaCrystalType)
    {
    }

    */
}

void RealSpaceBuilder::populateParticleFromParticleItem(RealSpaceModel* model,
                                                        const SessionItem& particleItem) const
{
    Particle3DContainer particle3DContainer;
    if (particleItem.modelType() == Constants::ParticleType) {
        auto pItem = dynamic_cast<const ParticleItem*>(&particleItem);
        auto particle = pItem->createParticle();
        particle3DContainer = RealSpaceBuilderUtils::singleParticle3DContainer(*particle);
    } else if (particleItem.modelType() == Constants::ParticleCoreShellType) {
        auto particleCoreShellItem = dynamic_cast<const ParticleCoreShellItem*>(&particleItem);
        // If there is no CORE or SHELL to populate inside ParticleCoreShellItem
        if (!particleCoreShellItem->getItem(ParticleCoreShellItem::T_CORE)
            || !particleCoreShellItem->getItem(ParticleCoreShellItem::T_SHELL))
            return;
        auto particleCoreShell = particleCoreShellItem->createParticleCoreShell();
        particle3DContainer
            = RealSpaceBuilderUtils::particleCoreShell3DContainer(*particleCoreShell);
    } else if (particleItem.modelType() == Constants::ParticleCompositionType) {
        auto particleCompositionItem = dynamic_cast<const ParticleCompositionItem*>(&particleItem);
        // If there is no particle to populate inside ParticleCompositionItem
        if (!particleCompositionItem->getItem(ParticleCompositionItem::T_PARTICLES))
            return;
        auto particleComposition = particleCompositionItem->createParticleComposition();
        particle3DContainer
            = RealSpaceBuilderUtils::particleComposition3DContainer(*particleComposition);
    } else if (particleItem.modelType() == Constants::ParticleDistributionType) {
        auto particleDistributionItem
            = dynamic_cast<const ParticleDistributionItem*>(&particleItem);
        // If there is no particle to populate inside ParticleDistributionItem
        if (!particleDistributionItem->getItem(ParticleDistributionItem::T_PARTICLES))
            return;

        // show nothing when ParticleDistributionItem is selected
    }

    populateParticleFromParticle3DContainer(model, particle3DContainer);
}

void RealSpaceBuilder::populateParticleFromParticle3DContainer(
    RealSpaceModel* model, const Particle3DContainer& particle3DContainer,
    const QVector3D& lattice_position) const
{
    if (particle3DContainer.containerSize()) {
        for (size_t i = 0; i < particle3DContainer.containerSize(); ++i) {
            auto particle3D = particle3DContainer.createParticle(i);
            particle3D->addTranslation(lattice_position);
            if (particle3D) {
                if (!particle3DContainer.particle3DBlend(i))
                    model->add(particle3D.release());
                else
                    model->addBlend(particle3D.release()); // use addBlend() for transparent object
            }
        }
    }
}
