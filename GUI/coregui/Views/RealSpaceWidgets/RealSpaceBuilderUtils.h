// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACEBUILDERUTILS_H
#define REALSPACEBUILDERUTILS_H

#include "WinDllMacros.h"
#include <QVector3D>
#include <memory>

class RealSpaceModel;
class SessionItem;
class SceneGeometry;
class RealSpaceBuilder;
class IRotation;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;
class IInterferenceFunction;
class Particle3DContainer;
namespace RealSpace
{
namespace Particles
{
class Particle;
}
}

namespace RealSpaceBuilderUtils
{
// compute cumulative abundances of particles
BA_CORE_API_ QVector<double> computeCumulativeAbundances(const SessionItem& layoutItem);

BA_CORE_API_ void populateParticlesAtLatticePositions(
    const std::vector<std::vector<double>>& lattice_positions,
    const std::vector<Particle3DContainer>& particle3DContainer_vector, RealSpaceModel* model,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D);

// No interference - random distribution of particles
BA_CORE_API_ void
populateRandomDistribution(RealSpaceModel* model, const SessionItem& layoutItem,
                           const std::vector<Particle3DContainer>& particle3DContainer_vector,
                           const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D);

BA_CORE_API_ std::vector<std::vector<double>>
computeRandomDistributionLatticePositions(const SessionItem& layoutItem,
                                          const SceneGeometry& sceneGeometry);

// InterferenceFunction2DLatticeType
BA_CORE_API_ void populateInterference2DLatticeType(
    const IInterferenceFunction* interference, RealSpaceModel* model,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D);

BA_CORE_API_ std::vector<std::vector<double>>
computeInterference2DLatticePositions(double l1, double l2, double l_alpha, double l_xi,
                                      const SceneGeometry& sceneGeometry);

// InterferenceFunction1DLatticeType
BA_CORE_API_ void populateInterference1DLatticeType(
    const IInterferenceFunction* interference, RealSpaceModel* model,
    const std::vector<Particle3DContainer>& particle3DContainer_vector,
    const SceneGeometry& sceneGeometry, const RealSpaceBuilder* builder3D);

// Implement Rotation of a 3D particle using parameters from IRotation Object
BA_CORE_API_ QVector3D implementParticleRotationfromIRotation(const IRotation*& rotation);

//! Apply transformations (translation, rotation) to a 3D Particle
//! or to a particle belonging to a ParticleComposition
BA_CORE_API_ void applyParticleTransformations(const Particle* particle,
                                               RealSpace::Particles::Particle* particle3D,
                                               const QVector3D& origin = QVector3D());

//! Apply transformations (translation, rotation) to a particle (core/shell) in a ParticleCoreShell
BA_CORE_API_ void applyParticleCoreShellTransformations(const Particle* particle,
                                                        RealSpace::Particles::Particle* particle3D,
                                                        const ParticleCoreShell* particleCoreShell,
                                                        const QVector3D& origin = QVector3D());

// Apply color to a 3D particle
BA_CORE_API_ void applyParticleColor(const Particle* particle,
                                     RealSpace::Particles::Particle* particle3D, double alpha = 1);

// Methods to populate different Particle Types
BA_CORE_API_ void populateParticleComposition(RealSpaceModel* model,
                                              const ParticleComposition* particleComposition,
                                              const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateParticleCoreShell(RealSpaceModel* model,
                                            const ParticleCoreShell* particleCoreShell,
                                            const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateParticleDistribution(RealSpaceModel* model,
                                               const ParticleDistribution* particleDistribution,
                                               const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateSingleParticle(RealSpaceModel* model, const Particle* particle,
                                         const QVector3D& origin = QVector3D());

BA_CORE_API_ std::vector<Particle3DContainer>
particle3DContainerVector(const SessionItem& layoutItem);

BA_CORE_API_ Particle3DContainer singleParticle3DContainer(const SessionItem* particleItem,
                                                           double total_abundance = 1.0);

BA_CORE_API_ Particle3DContainer particleCoreShell3DContainer(const SessionItem* particleItem,
                                                              double total_abundance = 1.0);

} // namespace RealSpaceBuilderUtils

#endif // REALSPACEBUILDERUTILS_H
