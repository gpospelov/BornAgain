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
#include <QVector>
#include <QVector3D>

class RealSpaceModel;
class SessionItem;
class SceneGeometry;
class RealSpaceBuilder;
class IRotation;
class Particle;
namespace RealSpace{ namespace Particles { class Particle; } }

namespace RealSpaceBuilderUtils
{
// compute cumulative abundances of particles
BA_CORE_API_ QVector<double> computeCumulativeAbundances(const SessionItem& layoutItem);

// No interference - random distribution of particles
BA_CORE_API_ void populateRandomDistribution(RealSpaceModel* model,
                                             const SessionItem& layoutItem,
                                             const SceneGeometry& sceneGeometry,
                                             const RealSpaceBuilder *builder3D);

BA_CORE_API_ QVector<QVector<double>> computeRandomDistributionLatticePositions(
        const SessionItem& layoutItem, const SceneGeometry &sceneGeometry);

// InterferenceFunction2DLatticeType
BA_CORE_API_ void populateInterference2DLatticeType(RealSpaceModel* model,
                                                    const SessionItem& layoutItem,
                                                    const SceneGeometry &sceneGeometry,
                                                    const RealSpaceBuilder *builder3D);

BA_CORE_API_ QVector<QVector<double>>  getInterference2DLatticePositions(
        const SessionItem& interference2DLatticeItem, const SceneGeometry &sceneGeometry);

BA_CORE_API_ QVector<QVector<double>> computeInterference2DLatticePositions(
        double l1, double l2, double l_alpha, double l_xi, const SceneGeometry& sceneGeometry);

// Implement Rotation of a 3D particle using parameters from IRotation Object
BA_CORE_API_ QVector3D implementParticleRotationfromIRotation(const IRotation *&rotation);

// Apply transformations (translation, rotation) to a 3D particle
BA_CORE_API_ void applyParticleTransformations(const Particle *particle,
                                               RealSpace::Particles::Particle *particle3D,
                                               const QVector3D &origin);

// Apply color to a 3D particle
BA_CORE_API_ void applyParticleColor(const Particle *particle,
                                     RealSpace::Particles::Particle *particle3D,
                                     double alpha = 1);

} // namespace RealSpaceBuilderUtils

#endif // REALSPACEBUILDERUTILS_H
