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
#include "Exceptions.h"
#include "FormFactorCrystal.h"
#include "IFormFactorDecorator.h"
#include "IParticle.h"
#include "InterferenceFunctionItems.h"
#include "InterferenceFunctions.h"
#include "Lattice2DItems.h"
#include "LayerItem.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include "MesoCrystal.h"
#include "MesoCrystalItem.h"
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
#include "RealSpaceMesoCrystalUtils.h"
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

kvector_t to_kvector(const QVector3D& origin)
{
    return kvector_t(static_cast<double>(origin.x()), static_cast<double>(origin.y()),
                     static_cast<double>(origin.z()));
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

// InterferenceFunctionFinite2DLatticeType
void RealSpaceBuilderUtils::populateInterferenceFinite2DLatticeType(
    const IInterferenceFunction* interference, RealSpaceModel* model,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D)
{
    auto interferenceFinite2D
        = dynamic_cast<const InterferenceFunctionFinite2DLattice*>(interference);
    const Lattice2D& lattice2D = interferenceFinite2D->lattice();

    int nc1 = static_cast<int>(interferenceFinite2D->numberUnitCells1());
    int nc2 = static_cast<int>(interferenceFinite2D->numberUnitCells2());

    double posVar = interferenceFinite2D->positionVariance();

    std::vector<std::vector<double>> lattice_positions
        = computeInterferenceFinite2DLatticePositions(lattice2D.length1(), lattice2D.length2(),
                                                      lattice2D.latticeAngle(),
                                                      lattice2D.rotationAngle(), nc1, nc2, posVar);

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

std::vector<std::vector<double>> RealSpaceBuilderUtils::computeInterferenceFinite2DLatticePositions(
    double l1, double l2, double l_alpha, double l_xi, int nc1, int nc2, double posVarFinite2D)
{
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    int n1m = nc1 / 2; // number of unit cells along -ve l1 axis
    int n1p = nc1 / 2; // number of unit cells along +ve l1 axis
    double center_offset1 = 0;
    if (nc1 % 2 == 0) { // if number of unit cells along l1 axis is even
        n1p = n1p - 1;
        center_offset1 = l1 / 2; // offset the particles in +ve l1 direction by 0.5*l1
    }

    int n2m = nc2 / 2; // number of unit cells along -ve l2 axis
    int n2p = nc2 / 2; // number of unit cells along +ve l2 axis
    double center_offset2 = 0;
    if (nc2 % 2 == 0) { // if number of unit cells along l2 axis is even
        n2p = n2p - 1;
        center_offset2 = l2 / 2; // offset the particles in +ve l2 direction by 0.5*l2
    }

    // used for finding position variance for if lattice is Finite 2D
    Distribution1DGaussSampler normalDist(0, posVarFinite2D);

    for (int i = -n1m; i <= n1p; ++i) {
        for (int j = -n2m; j <= n2p; ++j) {
            // For calculating lattice position vector v, we use: v = i*l1 + j*l2
            // where l1 and l2 are the lattice vectors,
            // i and j are the integer multiples of l1 and l2 respectively

            double posVarX = normalDist.randomSample();
            double posVarY = normalDist.randomSample();

            // x coordinate
            position.push_back((i * l1 + center_offset1) * std::cos(l_xi)
                               + (j * l2 + center_offset2) * std::cos(l_alpha + l_xi) + posVarX);
            // y coordinate
            position.push_back((i * l1 + center_offset1) * std::sin(l_xi)
                               + (j * l2 + center_offset2) * std::sin(l_alpha + l_xi) + posVarY);

            // no need for z coordinate as all lattice positions are calculated in the xy plane

            lattice_positions.push_back(position);
            position.clear();
        }
    }

    return lattice_positions;
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
    auto interference2DParacrystal
        = dynamic_cast<const InterferenceFunction2DParaCrystal*>(interference);

    RealSpace2DParacrystalUtils paracrystal2D(interference2DParacrystal, &sceneGeometry);

    std::vector<std::vector<double>> lattice_positions
        = paracrystal2D.compute2DParacrystalLatticePositions();

    populateParticlesAtLatticePositions(lattice_positions, particle3DContainer_vector, model,
                                        sceneGeometry, builder3D);
}

// Implement Rotation of a 3D particle using parameters from IRotation Object
RealSpace::Vector3D
RealSpaceBuilderUtils::implementParticleRotationfromIRotation(const IRotation*& rotation)
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
    return RealSpace::Vector3D(static_cast<float>(alpha), static_cast<float>(beta),
                               static_cast<float>(gamma));
}

void RealSpaceBuilderUtils::applyParticleTransformations(const Particle& particle,
                                                         RealSpace::Particles::Particle& particle3D,
                                                         const kvector_t& origin)
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
    RealSpace::Vector3D position(x + static_cast<float>(origin.x()),
                                 y + static_cast<float>(origin.y()),
                                 z + static_cast<float>(origin.z()));

    // If the particle belongs to a particle composition, along with the particle's
    // intrinsic transformations, position() and rotation() methods also account for the
    // translation and rotation (if present) of the particle composition as the
    // particleComposition's decompose() method already does this

    particle3D.addTransform(particle_rotate, position);
}

void RealSpaceBuilderUtils::applyParticleCoreShellTransformations(
    const Particle& particle, RealSpace::Particles::Particle& particle3D,
    const ParticleCoreShell& particleCoreShell, const kvector_t& origin)
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

    RealSpace::Vector3D position(static_cast<float>(P_clone->position().x() + origin.x()),
                                 static_cast<float>(P_clone->position().y() + origin.y()),
                                 static_cast<float>(P_clone->position().z() + origin.z()));

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
RealSpaceBuilderUtils::particle3DContainerVector(const SessionItem& layoutItem,
                                                 const QVector3D& origin)
{
    std::vector<Particle3DContainer> particle3DContainer_vector;

    double total_abundance = computeCumulativeAbundances(layoutItem).last();

    double cumulative_abundance = 0;

    for (auto particleItem : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES)) {

        Particle3DContainer particle3DContainer;

        if (particleItem->modelType() == Constants::ParticleType) {
            auto pItem = dynamic_cast<const ParticleItem*>(particleItem);
            auto particle = pItem->createParticle();
            particle3DContainer = singleParticle3DContainer(*particle, total_abundance, origin);
        } else if (particleItem->modelType() == Constants::ParticleCoreShellType) {
            auto particleCoreShellItem = dynamic_cast<const ParticleCoreShellItem*>(particleItem);
            // If there is no CORE or SHELL to populate inside ParticleCoreShellItem
            if (!particleCoreShellItem->getItem(ParticleCoreShellItem::T_CORE)
                || !particleCoreShellItem->getItem(ParticleCoreShellItem::T_SHELL))
                continue;
            auto particleCoreShell = particleCoreShellItem->createParticleCoreShell();
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell, total_abundance,
                                                               origin);
        } else if (particleItem->modelType() == Constants::ParticleCompositionType) {
            auto particleCompositionItem
                = dynamic_cast<const ParticleCompositionItem*>(particleItem);
            // If there is no particle to populate inside ParticleCompositionItem
            if (!particleCompositionItem->getItem(ParticleCompositionItem::T_PARTICLES))
                continue;
            auto particleComposition = particleCompositionItem->createParticleComposition();
            particle3DContainer
                = particleComposition3DContainer(*particleComposition, total_abundance, origin);
        } else if (particleItem->modelType() == Constants::ParticleDistributionType) {
            auto particleDistributionItem
                = dynamic_cast<const ParticleDistributionItem*>(particleItem);
            // If there is no particle to populate inside ParticleDistributionItem
            if (!particleDistributionItem->getItem(ParticleDistributionItem::T_PARTICLES))
                continue;
            auto particleDistribution = particleDistributionItem->createParticleDistribution();
            std::vector<Particle3DContainer> pd_ContainerVector
                = particleDistribution3DContainer(*particleDistribution, total_abundance, origin);
            for (size_t i = 0; i < pd_ContainerVector.size(); ++i) {
                cumulative_abundance += pd_ContainerVector[i].cumulativeAbundance();
                pd_ContainerVector[i].setCumulativeAbundance(cumulative_abundance);
                particle3DContainer_vector.emplace_back(std::move(pd_ContainerVector[i]));
            }
            continue;
        } else if (particleItem->modelType() == Constants::MesoCrystalType) {
            auto mesoCrystalItem = dynamic_cast<const MesoCrystalItem*>(particleItem);
            // If there is no particle to populate inside MesoCrystalItem
            if (!mesoCrystalItem->getItem(MesoCrystalItem::T_BASIS_PARTICLE))
                continue;
            particle3DContainer
                = RealSpaceBuilderUtils::mesoCrystal3DContainer(*mesoCrystalItem, total_abundance,
                                                                origin);
        }

        cumulative_abundance += particle3DContainer.cumulativeAbundance();
        particle3DContainer.setCumulativeAbundance(cumulative_abundance);
        particle3DContainer_vector.emplace_back(std::move(particle3DContainer));
    }

    return particle3DContainer_vector;
}

Particle3DContainer RealSpaceBuilderUtils::singleParticle3DContainer(const Particle& particle,
                                                                     double total_abundance, const QVector3D& origin)
{
    std::unique_ptr<Particle> P_clone(particle.clone()); // clone of the particle

    std::unique_ptr<const IFormFactor> particleff(P_clone->createFormFactor());
    auto ff = getUnderlyingFormFactor(particleff.get());

    auto particle3D = TransformTo3D::createParticlefromIFormFactor(ff);
    applyParticleTransformations(*P_clone, *particle3D, to_kvector(origin));
    applyParticleColor(*P_clone, *particle3D);

    Particle3DContainer singleParticle3DContainer;
    singleParticle3DContainer.addParticle(particle3D.release(), false);
    singleParticle3DContainer.setCumulativeAbundance(P_clone->abundance() / total_abundance);
    singleParticle3DContainer.setParticleType(Constants::ParticleType);

    return singleParticle3DContainer;
}

Particle3DContainer
RealSpaceBuilderUtils::particleCoreShell3DContainer(const ParticleCoreShell& particleCoreShell,
                                                    double total_abundance, const QVector3D& origin)
{
    // clone of the particleCoreShell
    std::unique_ptr<ParticleCoreShell> PCS_clone(particleCoreShell.clone());

    std::unique_ptr<const IFormFactor> coreParticleff(
        PCS_clone->coreParticle()->createFormFactor());
    std::unique_ptr<const IFormFactor> shellParticleff(
        PCS_clone->shellParticle()->createFormFactor());

    auto coreff = getUnderlyingFormFactor(coreParticleff.get());
    auto shellff = getUnderlyingFormFactor(shellParticleff.get());

    auto coreParticle3D = TransformTo3D::createParticlefromIFormFactor(coreff);
    auto shellParticle3D = TransformTo3D::createParticlefromIFormFactor(shellff);

    // core
    applyParticleCoreShellTransformations(*PCS_clone->coreParticle(), *coreParticle3D, *PCS_clone,
                                          to_kvector(origin));
    applyParticleColor(*PCS_clone->coreParticle(), *coreParticle3D);

    // shell (set an alpha value of 0.5 for transparency)
    applyParticleCoreShellTransformations(*PCS_clone->shellParticle(), *shellParticle3D,
                                          *PCS_clone, to_kvector(origin));
    applyParticleColor(*PCS_clone->shellParticle(), *shellParticle3D, 0.5);

    Particle3DContainer particleCoreShell3DContainer;

    particleCoreShell3DContainer.addParticle(coreParticle3D.release(), false); // index 0
    particleCoreShell3DContainer.addParticle(shellParticle3D.release(), true); // index 1
    particleCoreShell3DContainer.setCumulativeAbundance(PCS_clone->abundance() / total_abundance);
    particleCoreShell3DContainer.setParticleType(Constants::ParticleCoreShellType);

    return particleCoreShell3DContainer;
}

Particle3DContainer RealSpaceBuilderUtils::particleComposition3DContainer(
        const ParticleComposition& particleComposition, double total_abundance,
        const QVector3D& origin)
{
    // clone of the particleComposition
    std::unique_ptr<ParticleComposition> PC_clone(particleComposition.clone());

    SafePointerVector<IParticle> pc_vector = PC_clone->decompose();

    Particle3DContainer particleComposition3DContainer;

    for (const IParticle* pc_particle : pc_vector) {
        Particle3DContainer particle3DContainer;
        // no abundances are associated with the individual components of ParticleComposition
        if (dynamic_cast<const ParticleCoreShell*>(pc_particle)) {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pc_particle);
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell, 1.0, origin);
        } else if (dynamic_cast<const MesoCrystal*>(pc_particle)) {
            // TODO: Implement method to populate MesoCrystal from CORE and NOT from MesoCrystalItem
            // as it is done currently in RealSpaceBuilderUtils::mesoCrystal3DContainer
            std::ostringstream ostr;
            ostr << "Sorry, MesoCrystal inside ParticleComposition not yet implemented";
            ostr << "\n\nStay tuned!";
            throw Exceptions::ClassInitializationException(ostr.str());
        } else {
            auto particle = dynamic_cast<const Particle*>(pc_particle);
            particle3DContainer = singleParticle3DContainer(*particle, 1.0, origin);
        }
        // add particles from 3Dcontainer of core-shell/particle into particleComposition3DContainer
        for (size_t i = 0; i < particle3DContainer.containerSize(); ++i) {
            particleComposition3DContainer.addParticle(
                particle3DContainer.createParticle(i).release(),
                particle3DContainer.particle3DBlend(i));
        }
    }
    // set the correct abundance for the entire ParticleComposition
    particleComposition3DContainer.setCumulativeAbundance(PC_clone->abundance() / total_abundance);
    particleComposition3DContainer.setParticleType(Constants::ParticleCompositionType);
    return particleComposition3DContainer;
}

std::vector<Particle3DContainer> RealSpaceBuilderUtils::particleDistribution3DContainer(
        const ParticleDistribution& particleDistribution, double total_abundance,
        const QVector3D& origin)
{
    auto pd_vector = particleDistribution.generateParticles();

    std::vector<Particle3DContainer> particleDistribution3DContainer_vector;

    for (auto pd_particle : pd_vector) {
        Particle3DContainer particle3DContainer;
        if (dynamic_cast<const ParticleComposition*>(pd_particle)) {
            auto particleComposition = dynamic_cast<const ParticleComposition*>(pd_particle);
            particle3DContainer
                = particleComposition3DContainer(*particleComposition, total_abundance, origin);
        } else if (dynamic_cast<const ParticleCoreShell*>(pd_particle)) {
            auto particleCoreShell = dynamic_cast<const ParticleCoreShell*>(pd_particle);
            particle3DContainer = particleCoreShell3DContainer(*particleCoreShell, total_abundance,
                                                               origin);
        } else if (dynamic_cast<const MesoCrystal*>(pd_particle)) {
            // TODO: Implement method to populate MesoCrystal from CORE and NOT from MesoCrystalItem
            // as it is done currently in RealSpaceBuilderUtils::mesoCrystal3DContainer
            std::ostringstream ostr;
            ostr << "Sorry, MesoCrystal inside ParticleDistribution not yet implemented";
            ostr << "\n\nStay tuned!";
            throw Exceptions::ClassInitializationException(ostr.str());
        } else {
            auto particle = dynamic_cast<const Particle*>(pd_particle);
            particle3DContainer = singleParticle3DContainer(*particle, total_abundance, origin);
        }
        particleDistribution3DContainer_vector.emplace_back(std::move(particle3DContainer));
    }
    return particleDistribution3DContainer_vector;
}

Particle3DContainer
RealSpaceBuilderUtils::mesoCrystal3DContainer(const MesoCrystalItem& mesoCrystalItem,
                                              double total_abundance, const QVector3D& origin)
{
    RealSpaceMesoCrystal mesoCrystalUtils(&mesoCrystalItem, total_abundance, origin);

    Particle3DContainer mesoCrystal3DContainer = mesoCrystalUtils.populateMesoCrystal();

    return mesoCrystal3DContainer;
}
