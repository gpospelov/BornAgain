// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.cpp
//! @brief     Implements RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceBuilderUtils.h"
#include "IFormFactorDecorator.h"
#include "IParticle.h"
#include "InterferenceFunctionItems.h"
#include "InterferenceFunctions.h"
#include "Lattice2DItems.h"
#include "LayerItem.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include "MultiLayerItem.h"
#include "Particle.h"
#include "Particle3DContainer.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShell.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistribution.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "RealSpace2DParacrystalUtils.h"
#include "RealSpaceBuilder.h"
#include "RealSpaceCanvas.h"
#include "RealSpaceModel.h"
#include "RotationItems.h"
#include "Rotations.h"
#include "SessionItem.h"
#include "TransformTo3D.h"
#include "TransformationItem.h"
#include "Units.h"
#include "VectorItem.h"
#include <AppSvc.h>

namespace
{
const double layerBorderWidth = 10.0;

const IFormFactor* getUnderlyingFormFactor(const IFormFactor* ff)
{
    // TRUE as long as ff is of IFormFactorDecorator (or its derived) type
    while (dynamic_cast<const IFormFactorDecorator*>(ff))
        ff = dynamic_cast<const IFormFactorDecorator*>(ff)->getFormFactor();

    return ff;
}
}

// compute cumulative abundances of particles
QVector<double> RealSpaceBuilderUtils::computeCumulativeAbundances(const SessionItem& layoutItem)
{
    // Retrieving abundances of particles
    double total_abundance = 0.0;
    QVector<double> cumulative_abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES)) {
        total_abundance
            = total_abundance + particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        cumulative_abundances.append(total_abundance);
    }

    return cumulative_abundances;
}

void RealSpaceBuilderUtils::populateParticlesAtLatticePositions(
    const std::vector<std::vector<double>>& lattice_positions,
    const std::vector<Particle3DContainer>& particle3DContainer_vector, RealSpaceModel* model,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    double layer_size = sceneGeometry.layer_size();
    double layer_thickness
        = std::max(sceneGeometry.layer_top_thickness(), sceneGeometry.layer_bottom_thickness());

    for (std::vector<double> position : lattice_positions) {
        // for random selection of particles based on their abundances
        double rand_num = (rand() / static_cast<double>(RAND_MAX)); // (between 0 and 1)
        int k = 0;

        for (const auto& particle3DContainer : particle3DContainer_vector) {
            if (rand_num <= particle3DContainer.cumulativeAbundance()) {
                // lattice position + location (TO BE ADDED)
                double pos_x = position[0];
                double pos_y = position[1];
                double pos_z = 0;

                if (std::abs(pos_x) <= layer_size - layerBorderWidth
                    && std::abs(pos_y) <= layer_size - layerBorderWidth
                    && std::abs(pos_z) <= layer_thickness) {

                    builder3D->populateParticleFromParticle3DContainer(
                        model, particle3DContainer,
                        QVector3D(static_cast<float>(position[0]), static_cast<float>(position[1]),
                                  static_cast<float>(0)));
                }
                break;
            } else
                ++k;
        }
    }
}

// No interference - random distribution of particles
void RealSpaceBuilderUtils::populateRandomDistribution(
    RealSpaceModel* model, const SessionItem& layoutItem,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    // get the lattice positions at which to populate the particles
    std::vector<std::vector<double>> lattice_positions
        = computeRandomDistributionLatticePositions(layoutItem, sceneGeometry);

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

std::vector<std::vector<double>>
RealSpaceBuilderUtils::computeRandomDistributionLatticePositions(const SessionItem& layoutItem,
                                                                 const SceneGeometry& sceneGeometry)
{
    double layer_size = sceneGeometry.layer_size();
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    // to compute total number of particles we use the total particle density
    // and multiply by the area of the layer
    double total_density = layoutItem.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble();
    int num_particles = static_cast<int>(total_density * (2 * layer_size) * (2 * layer_size));

    for (int i = 1; i <= num_particles; ++i) {
        // For calculating lattice coordinates we use random x and y coordinates
        position.push_back((rand() / static_cast<double>(RAND_MAX)) * 2 * layer_size
                           - layer_size); // x
        position.push_back((rand() / static_cast<double>(RAND_MAX)) * 2 * layer_size
                           - layer_size); // y

        // no need for z coordinate as all lattice positions are calculated in the xy plane

        lattice_positions.push_back(position);
        position.clear();
    }

    return lattice_positions;
}

// InterferenceFunction2DLatticeType
void RealSpaceBuilderUtils::populateInterference2DLatticeType(
    const IInterferenceFunction* interference, RealSpaceModel* model,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    auto interference2D = dynamic_cast<const InterferenceFunction2DLattice*>(interference);
    const Lattice2D& lattice2D = interference2D->lattice();

    std::vector<std::vector<double>> lattice_positions = computeInterference2DLatticePositions(
        lattice2D.length1(), lattice2D.length2(), lattice2D.latticeAngle(),
        lattice2D.rotationAngle(), sceneGeometry);

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

std::vector<std::vector<double>> RealSpaceBuilderUtils::computeInterference2DLatticePositions(
    double l1, double l2, double l_alpha, double l_xi, const SceneGeometry& sceneGeometry)
{
    double layer_size = sceneGeometry.layer_size();
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    // Estimate the limit n1 and n2 of the integer multiple i and j of the lattice vectors required
    // for populating particles correctly within the 3D model's boundaries
    int n1 = 0, n2 = 0;
    n1 = l1 == 0.0 ? 2 : static_cast<int>(layer_size * 2 / l1);

    // This condition is required when this function is used to compute 1D Lattice positions
    if (l2 != 0) {
        n2 = l2 == 0.0 ? 2 : static_cast<int>(layer_size * 2 / l2);

        n1 = std::max(n1, n2);
        n2 = std::max(n1, n2);
    }

    for (int i = -n1; i <= n1; ++i) {
        for (int j = -n2; j <= n2; ++j) {
            // For calculating lattice position vector v, we use: v = i*l1 + j*l2
            // where l1 and l2 are the lattice vectors,
            // i and j are the integer multiples of l1 and l2 respectively

            position.push_back(i * l1 * std::cos(l_xi)
                               + j * l2 * std::cos(l_alpha + l_xi)); // x coordinate
            position.push_back(i * l1 * std::sin(l_xi)
                               + j * l2 * std::sin(l_alpha + l_xi)); // y coordinate

            // no need for z coordinate as all lattice positions are calculated in the xy plane

            lattice_positions.push_back(position);
            position.clear();
        }
    }

    return lattice_positions;
}

void RealSpaceBuilderUtils::populateInterference1DLatticeType(
    const IInterferenceFunction* interference, RealSpaceModel* model,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    auto interference1D = dynamic_cast<const InterferenceFunction1DLattice*>(interference);
    auto interference1DParameters = interference1D->getLatticeParameters();

    // Simply set the parameters l1 = l, l2 = 0, l_alpha = 0 and l_xi = l_xi in
    // computeInterference2DLatticePositions() to compute lattice positions for 1D Lattice
    std::vector<std::vector<double>> lattice_positions = computeInterference2DLatticePositions(
        interference1DParameters.m_length, 0.0, 0.0, interference1DParameters.m_xi, sceneGeometry);

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

void RealSpaceBuilderUtils::populateRadialParacrystalType(
    const IInterferenceFunction* interference, RealSpaceModel* model,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    auto interferenceRadialParacrystal
        = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(interference);
    auto peakDistance = interferenceRadialParacrystal->peakDistance();

    double layer_size = sceneGeometry.layer_size();
    std::vector<std::vector<double>> lattice_positions;

    // Estimate the limit n of the integer multiple i of the peakDistance required
    // for populating particles correctly within the 3D model's boundaries
    int n = static_cast<int>(layer_size * 2) / static_cast<int>(peakDistance);

    lattice_positions.resize(static_cast<size_t>(2 * n + 1));
    for (auto& it : lattice_positions) {
        it.resize(2);
    }

    lattice_positions[0][0] = 0.0; // x coordinate of reference particle - at the origin
    lattice_positions[0][1] = 0.0; // y coordinate of reference particle - at the origin

    for (int i = 1; i <= 2 * n; ++i) {
        // positions of particles located along +x (store every odd index of lattice_positions)
        size_t k1 = 0;
        if (i - 2 > 0)
            k1 = static_cast<size_t>(i - 2);

        double offset = interferenceRadialParacrystal->randomSample();
        lattice_positions[static_cast<size_t>(i)][0]
            = lattice_positions[k1][0] + peakDistance + offset; // x coordinate
        lattice_positions[static_cast<size_t>(i)][1] = 0.0;     // y coordinate

        // positions of particles located along -x (store every even index of lattice_positions)
        ++i;

        size_t k2 = 0;
        if (i - 2 > 0)
            k2 = static_cast<size_t>(i - 2);

        offset = interferenceRadialParacrystal->randomSample();
        lattice_positions[static_cast<size_t>(i)][0]
            = lattice_positions[k2][0] - peakDistance + offset; // x coordinate
        lattice_positions[static_cast<size_t>(i)][1] = 0.0;     // y coordinate
    }

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

void RealSpaceBuilderUtils::populate2DParacrystalType(
        const IInterferenceFunction* interference, RealSpaceModel* model,
        const std::vector<Particle3DContainer>& particle3DContainer_vector,
        const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    auto interference2DParacrystal =
            dynamic_cast<const InterferenceFunction2DParaCrystal*>(interference);

    RealSpace2DParacrystalUtils paracrystal2D(interference2DParacrystal, &sceneGeometry);

    std::vector<std::vector<double>> lattice_positions =
            paracrystal2D.compute2DParacrystalLatticePositions();

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

// Implement Rotation of a 3D particle using parameters from IRotation Object
QVector3D RealSpaceBuilderUtils::implementParticleRotationfromIRotation(const IRotation*& rotation)
{
    double alpha = 0.0;
    double beta = 0.0;
    double gamma = 0.0;

    if (auto rotX = dynamic_cast<const RotationX*>(rotation)) {
        beta = rotX->getAngle(); // about x-axis
    } else if (auto rotY = dynamic_cast<const RotationY*>(rotation)) {
        alpha = Units::deg2rad(90.0);
        beta = rotY->getAngle(); // about y-axis
        gamma = Units::deg2rad(-90.0);
    } else if (auto rotZ = dynamic_cast<const RotationZ*>(rotation)) {
        alpha = rotZ->getAngle(); // about z-axis
    } else if (auto rotEuler = dynamic_cast<const RotationEuler*>(rotation)) {
        alpha = rotEuler->getAlpha();
        beta = rotEuler->getBeta();
        gamma = rotEuler->getGamma();
    }
    return QVector3D(static_cast<float>(alpha), static_cast<float>(beta),
                     static_cast<float>(gamma));
}

void RealSpaceBuilderUtils::applyParticleTransformations(const Particle& particle,
                                                         RealSpace::Particles::Particle& particle3D,
                                                         const QVector3D& origin)
{
    // rotation
    RealSpace::Vector3D particle_rotate;
    const IRotation* rotation = particle.rotation();

    if (rotation)
        particle_rotate = implementParticleRotationfromIRotation(rotation);

    // translation
    float x = static_cast<float>(particle.position().x());
    float y = static_cast<float>(particle.position().y());
    float z = static_cast<float>(particle.position().z());
    RealSpace::Vector3D position(x + origin.x(), y + origin.y(), z + origin.z());

    // If the particle belongs to a particle composition, along with the particle's
    // intrinsic transformations, position() and rotation() methods also account for the
    // translation and rotation (if present) of the particle composition as the
    // particleComposition's decompose() method already does this

    particle3D.addTransform(particle_rotate, position);
}

void RealSpaceBuilderUtils::applyParticleCoreShellTransformations(
    const Particle& particle, RealSpace::Particles::Particle& particle3D,
    const ParticleCoreShell& particleCoreShell, const QVector3D& origin)
{
    std::unique_ptr<Particle> P_clone(particle.clone()); // clone of the current particle

    // rotation
    RealSpace::Vector3D particle_rotate;
    const IRotation* rotationCoreShell = particleCoreShell.rotation();

    if (rotationCoreShell)
        P_clone->rotate(*rotationCoreShell);

    const IRotation* rotation = P_clone->rotation();

    if (rotation)
        particle_rotate = implementParticleRotationfromIRotation(rotation);

    // translation
    kvector_t positionCoreShell = particleCoreShell.position();

    P_clone->translate(positionCoreShell);

    RealSpace::Vector3D position(static_cast<float>(P_clone->position().x()) + origin.x(),
                                 static_cast<float>(P_clone->position().y()) + origin.y(),
                                 static_cast<float>(P_clone->position().z()) + origin.z());

    particle3D.transform(particle_rotate, position);
}

void RealSpaceBuilderUtils::applyParticleColor(const Particle& particle,
                                               RealSpace::Particles::Particle& particle3D,
                                               double alpha)
{
    // assign correct color to the particle from the knowledge of its material
    const Material* particle_material = particle.material();
    QString material_name = QString::fromStdString(particle_material->getName());
    auto materialItem = AppSvc::materialModel()->materialFromName(material_name);
    QColor color = materialItem->color();
    color.setAlphaF(alpha);
    particle3D.color = color;
}

std::vector<Particle3DContainer>
RealSpaceBuilderUtils::particle3DContainerVector(const SessionItem& layoutItem)
{
    std::vector<Particle3DContainer> particle3DContainer_vector;

    double total_abundance = computeCumulativeAbundances(layoutItem).last();

    double cumulative_abundance = 0;

    for (auto particleItem : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES)) {

        Particle3DContainer particle3DContainer;

        if (particleItem->modelType() == Constants::ParticleType) {
            auto pItem = dynamic_cast<const ParticleItem*>(particleItem);
            auto particle = pItem->createParticle();
            particle3DContainer = singleParticle3DContainer(*particle, total_abundance);
        } else if (particleItem->modelType() == Constants::ParticleCoreShellType) {
            auto particleCoreShellItem = dynamic_cast<const ParticleCoreShellItem*>(particleItem);
            // If there is no CORE or SHELL to populate inside ParticleCoreShellItem
            if (!particleCoreShellItem->getItem(ParticleCoreShellItem::T_CORE)
                || !particleCoreShellItem->getItem(ParticleCoreShellItem::T_SHELL))
                continue;
            auto particleCoreShell = particleCoreShellItem->createParticleCoreShell();
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell, total_abundance);
        } else if (particleItem->modelType() == Constants::ParticleCompositionType) {
            auto particleCompositionItem
                = dynamic_cast<const ParticleCompositionItem*>(particleItem);
            // If there is no particle to populate inside ParticleCompositionItem
            if (!particleCompositionItem->getItem(ParticleCompositionItem::T_PARTICLES))
                continue;
            auto particleComposition = particleCompositionItem->createParticleComposition();
            particle3DContainer
                = particleComposition3DContainer(*particleComposition, total_abundance);
        } else if (particleItem->modelType() == Constants::ParticleDistributionType) {
            auto particleDistributionItem
                = dynamic_cast<const ParticleDistributionItem*>(particleItem);
            // If there is no particle to populate inside ParticleDistributionItem
            if (!particleDistributionItem->getItem(ParticleDistributionItem::T_PARTICLES))
                continue;
            auto particleDistribution = particleDistributionItem->createParticleDistribution();
            std::vector<Particle3DContainer> pd_ContainerVector
                = particleDistribution3DContainer(*particleDistribution, total_abundance);
            for (size_t i = 0; i < pd_ContainerVector.size(); ++i) {
                cumulative_abundance += pd_ContainerVector[i].cumulativeAbundance();
                pd_ContainerVector[i].setCumulativeAbundance(cumulative_abundance);
                particle3DContainer_vector.emplace_back(std::move(pd_ContainerVector[i]));
            }
            continue;
        }
        cumulative_abundance += particle3DContainer.cumulativeAbundance();
        particle3DContainer.setCumulativeAbundance(cumulative_abundance);
        particle3DContainer_vector.emplace_back(std::move(particle3DContainer));
    }

    return particle3DContainer_vector;
}

Particle3DContainer RealSpaceBuilderUtils::singleParticle3DContainer(const Particle& particle,
                                                                     double total_abundance)
{
    std::unique_ptr<const IFormFactor> particleff(particle.createFormFactor());
    auto ff = getUnderlyingFormFactor(particleff.get());

    auto particle3D = TransformTo3D::createParticlefromIFormFactor(ff);
    applyParticleTransformations(particle, *particle3D);
    applyParticleColor(particle, *particle3D);

    Particle3DContainer singleParticle3DContainer;
    singleParticle3DContainer.addParticle(particle3D.release(), false);
    singleParticle3DContainer.setCumulativeAbundance(particle.abundance() / total_abundance);
    singleParticle3DContainer.setParticleType(Constants::ParticleType);

    return singleParticle3DContainer;
}

Particle3DContainer
RealSpaceBuilderUtils::particleCoreShell3DContainer(const ParticleCoreShell& particleCoreShell,
                                                    double total_abundance)
{
    std::unique_ptr<const IFormFactor> coreParticleff(
        particleCoreShell.coreParticle()->createFormFactor());
    std::unique_ptr<const IFormFactor> shellParticleff(
        particleCoreShell.shellParticle()->createFormFactor());

    auto coreff = getUnderlyingFormFactor(coreParticleff.get());
    auto shellff = getUnderlyingFormFactor(shellParticleff.get());

    auto coreParticle3D = TransformTo3D::createParticlefromIFormFactor(coreff);
    auto shellParticle3D = TransformTo3D::createParticlefromIFormFactor(shellff);

    // core
    applyParticleCoreShellTransformations(*particleCoreShell.coreParticle(), *coreParticle3D,
                                          particleCoreShell);
    applyParticleColor(*particleCoreShell.coreParticle(), *coreParticle3D);

    // shell (set an alpha value of 0.5 for transparency)
    applyParticleCoreShellTransformations(*particleCoreShell.shellParticle(), *shellParticle3D,
                                          particleCoreShell);
    applyParticleColor(*particleCoreShell.shellParticle(), *shellParticle3D, 0.5);

    Particle3DContainer particleCoreShell3DContainer;

    particleCoreShell3DContainer.addParticle(coreParticle3D.release(), false); // index 0
    particleCoreShell3DContainer.addParticle(shellParticle3D.release(), true); // index 1
    particleCoreShell3DContainer.setCumulativeAbundance(particleCoreShell.abundance()
                                                        / total_abundance);
    particleCoreShell3DContainer.setParticleType(Constants::ParticleCoreShellType);

    return particleCoreShell3DContainer;
}

Particle3DContainer RealSpaceBuilderUtils::particleComposition3DContainer(
    const ParticleComposition& particleComposition, double total_abundance)
{
    SafePointerVector<IParticle> pc_vector = particleComposition.decompose();

    Particle3DContainer particleComposition3DContainer;

    for (const IParticle* pc_particle : pc_vector) {

        Particle3DContainer particle3DContainer;
        // no abundances are associated with the individual components of ParticleComposition
        if (dynamic_cast<const ParticleCoreShell*>(pc_particle)) {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pc_particle);
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell);
        } else {
            auto particle = dynamic_cast<const Particle*>(pc_particle);
            particle3DContainer = singleParticle3DContainer(*particle);
        }
        // add particles from 3Dcontainer of core-shell/particle into particleComposition3DContainer
        for (size_t i = 0; i < particle3DContainer.containerSize(); ++i) {
            particleComposition3DContainer.addParticle(
                particle3DContainer.createParticle(i).release(),
                particle3DContainer.particle3DBlend(i));
        }
    }
    // set the correct abundance for the entire ParticleComposition
    particleComposition3DContainer.setCumulativeAbundance(particleComposition.abundance()
                                                          / total_abundance);
    particleComposition3DContainer.setParticleType(Constants::ParticleCompositionType);
    return particleComposition3DContainer;
}

std::vector<Particle3DContainer> RealSpaceBuilderUtils::particleDistribution3DContainer(
    const ParticleDistribution& particleDistribution, double total_abundance)
{
    auto pd_vector = particleDistribution.generateParticles();

    std::vector<Particle3DContainer> particleDistribution3DContainer_vector;

    for (auto pd_particle : pd_vector) {
        Particle3DContainer particle3DContainer;
        if (dynamic_cast<const ParticleComposition*>(pd_particle)) {
            auto particleComposition = dynamic_cast<const ParticleComposition*>(pd_particle);
            particle3DContainer
                = particleComposition3DContainer(*particleComposition, total_abundance);
        } else if (dynamic_cast<const ParticleCoreShell*>(pd_particle)) {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pd_particle);
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell, total_abundance);
        } else {
            auto particle = dynamic_cast<const Particle*>(pd_particle);
            particle3DContainer = singleParticle3DContainer(*particle, total_abundance);
        }
        particleDistribution3DContainer_vector.emplace_back(std::move(particle3DContainer));
    }
    return particleDistribution3DContainer_vector;
}
